
#include "usb_com.hpp"
#include <cstdarg>
#include <client/bt_client.hpp>

ap_memory_t ap_memory = {0, };

USBCom::USBCom(asio::io_context* io_context, BTClient* bt_client):
  timer(*io_context),
  timer_ping(*io_context) {
  check();
  ping(false);
  this->bt_client = bt_client;
  ap_memory.pc.settings.dialog_character = 0xFF;
}

void USBCom::check() {
  int wait = (int)(1/60.0*1000);
  if (read() != FT_OK) {
    status = USB_STATUS_DISCONNECTED;
    FT_Close(handle);
    if (open() != FT_OK) wait = 1000;
  }
  else process();

  timer.expires_after(std::chrono::milliseconds(wait));
  timer.async_wait([this](const asio::error_code& error) {
    if (!error) check();
  });
}

void USBCom::ping(bool check) {
  if (check) {
    switch (status) {
      case USB_STATUS_CONNECTED:
        status |= USB_STATUS_PINGED;
        break;
      case USB_STATUS_CONNECTED|USB_STATUS_PINGED:
        log("[ PC] Ping Timeout...\n");
        status = USB_STATUS_DISCONNECTED;
        break;
    }
  }
  else status &= ~USB_STATUS_PINGED;

  timer_ping.expires_after(std::chrono::milliseconds(2500));
  timer_ping.async_wait([this](const asio::error_code& error) {
    if (!error) ping(true);
  });
}

FT_STATUS USBCom::open() {
  uint8_t opened = 0;
  DWORD devices;
  if (FT_CreateDeviceInfoList(&devices) != FT_OK) return FT_OTHER_ERROR;
  if (devices) {
    FT_DEVICE_LIST_INFO_NODE dev_info[devices];
    if (FT_GetDeviceInfoList(dev_info, &devices) != FT_OK) return FT_OTHER_ERROR;
    for (DWORD i = 0; i < devices; i++) {
      if (!strcmp(dev_info[i].Description, "FT245R USB FIFO") && dev_info[i].ID == 0x4036001) {
        if (FT_Open(i, &handle) != FT_OK) return FT_OTHER_ERROR;
        opened = 1;
        FT_ResetDevice(handle);
        FT_SetTimeouts(handle, 10000, 10000);
        FT_Purge(handle, FT_PURGE_RX | FT_PURGE_TX);
      }
    }
  }
  if (!opened) return FT_OTHER_ERROR;
  return FT_OK;
}

FT_STATUS USBCom::read() {
  packet.cmd = USB_CMD_NONE;
  FT_STATUS status;
  DWORD pending = 0;
  DWORD size = 0;
  status = FT_GetQueueStatus(handle, &pending);
  if (pending >= 8) {
    if (FT_Read(handle, packet.raw, 8, &size) != FT_OK || size != 8) return FT_OTHER_ERROR;
    endian_swap16(&packet.cmd);
    endian_swap16(&packet.size);
    log("[N64] cmd:%u size:%u data:0x", packet.cmd, packet.size);
    for (int i = 0; i < 4; i++) log("%.2X", packet.data[i]);
    if (packet.size) {
      packet.size--;
      packet.size = packet.size-packet.size%4+4;
      if (packet.size > 504) packet.cmd = USB_CMD_NONE;
      else if (FT_Read(handle, packet.extra, packet.size, &size) != FT_OK || size != packet.size) return FT_OTHER_ERROR;
      log(" extra:0x");
      for (int i = 0; i < size; i++) log("%.2X", packet.extra[i]);
    }
    log("\n");
    endian_swap_packet();
  }
  else if (pending > 0) FT_Purge(handle, FT_PURGE_RX);
  return status;
}

FT_STATUS USBCom::write(uint16_t cmd, uint16_t len) {
  DWORD size;
  if (len) {
    len--;
    len = len-len%4+4;
  }
  packet.cmd = cmd;
  packet.size = len;
  endian_swap_packet();
  endian_swap16(&packet.cmd);
  endian_swap16(&packet.size);
  FT_STATUS ret = (FT_Write(handle, packet.raw, len+8, &size) != FT_OK || size != len+8) ? FT_OTHER_ERROR : FT_OK;
  log("[ PC] cmd:%u size:%u data:0x", cmd, len);
  for (int i = 0; i < 4; i++) log("%.2X", packet.data[i]);
  if (len) {
    log(" extra:0x", len);
    for (int i = 0; i < size-8; i++) log("%.2X", packet.extra[i]);
  }
  log("\n");
  return ret;
}

void USBCom::process() {
  if (packet.cmd == USB_CMD_NONE) return;
  ping(false);
  switch (status & ~USB_STATUS_PINGED) {
    case USB_STATUS_DISCONNECTED:
      switch (packet.cmd) {
        case USB_CMD_HANDSHAKE:
          log("[N64] USB_CMD_HANDSHAKE\n");
          if (memcmp(packet.handshake.msg, "HELO", 4)) {
            log("USB Protocol invalid handshake message!\n");
            return;
          }
          if (packet.handshake.version.as_int != AP_VERSION.as_int) {
            log("USB Protocol version mismatch! We are: 0x");
            for (int i = 0; i < 4; i++) log("%.2X", ((u8*)&AP_VERSION.as_int)[i]);
            log(" they are: 0x");
            for (int i = 0; i < 4; i++) log("%.2X", ((u8*)&packet.handshake.version.as_int)[i]);
            log("\n");
            return;
          }
          memcpy(packet.handshake.msg, "'LO!", 4);
          packet.handshake.version.as_int = AP_VERSION.as_int;
          write(USB_CMD_HANDSHAKE, 4);
          status = USB_STATUS_CONNECTING;
          break;
      }
      break;
    case USB_STATUS_CONNECTING:
      switch (packet.cmd) {
        case USB_CMD_PING:
          log("[N64] USB_CMD_PING\n");
          write(USB_CMD_PONG, packet.size);
          status = USB_STATUS_CONNECTED;
          ap_memory.n64.misc.show_message = 0;
          ap_memory.n64.misc.death_link_us = 0;
          ap_memory.n64.misc.death_link_ap = 0;
          ap_memory.pc.misc.death_link_us = 0;
          ap_memory.pc.misc.death_link_ap = 0;
          ap_memory.pc.misc.show_message = 0;
          for (int i = 0; i < sizeof(ap_memory_pc_t); i++) ((u8*)&apm_clone)[i] = 0;
          break;
        default:
          log("[N64] Unexpected packet. Disconnected.\n");
          status = USB_STATUS_DISCONNECTED;
      }
      break;
    case USB_STATUS_CONNECTED:
      switch (packet.cmd) {
        case USB_CMD_PING:
          log("[N64] USB_CMD_PING\n");
          write(USB_CMD_PONG, packet.size);
          break;
        case USB_CMD_N64_MISC:
          log("[N64] USB_CMD_N64_MISC\n");
          memcpy(&ap_memory.n64.misc, packet.extra, packet.size);
          endian_swap16(&ap_memory.n64.misc.current_map);
          break;
        case USB_CMD_N64_SAVES_REAL:
          log("[N64] USB_CMD_N64_SAVES_REAL\n");
          memcpy(&ap_memory.n64.saves.real, packet.extra, packet.size);
          endian_swap_save(&ap_memory.n64.saves.real);
          break;
        case USB_CMD_N64_SAVES_FAKE:
          log("[N64] USB_CMD_N64_SAVES_FAKE\n");
          memcpy(&ap_memory.n64.saves.fake, packet.extra, packet.size);
          endian_swap_save(&ap_memory.n64.saves.fake);
          break;
        case USB_CMD_N64_SAVES_NESTS:
          log("[N64] USB_CMD_N64_SAVES_NESTS\n");
          memcpy(&ap_memory.n64.saves.nests, packet.extra, packet.size);
          break;
        default:
          log("[N64] Unexpected packet. Disconnected.\n");
          status = USB_STATUS_DISCONNECTED;
      }
      break;
  }
  if (status == USB_STATUS_CONNECTED && bt_client->get_state() == bt_client->STATE_OK) send();
}

bool USBCom::check_changes(void* _real, void* _clone, int size) {
  uint8_t* real = (uint8_t*)_real;
  uint8_t* clone = (uint8_t*)_clone;
  bool different = false;
  for (int i = 0; i < size; i++) {
    if (clone[i] != real[i]) {
      clone[i] = real[i];
      different = true;
    }
  }
  return different;
}

void USBCom::send() {
  bool message = check_changes(&ap_memory.pc.message, &apm_clone.message, sizeof(apm_clone.message));
  bool misc = check_changes(&ap_memory.pc.misc, &apm_clone.misc, sizeof(apm_clone.misc));
  bool settings = check_changes(&ap_memory.pc.settings, &apm_clone.settings, sizeof(apm_clone.settings));
  bool items = check_changes(&ap_memory.pc.items, &apm_clone.items, sizeof(apm_clone.items));
  bool traps = check_changes(&ap_memory.pc.traps, &apm_clone.traps, sizeof(apm_clone.traps));
  bool exit_map = check_changes(&ap_memory.pc.exit_map, &apm_clone.exit_map, sizeof(apm_clone.exit_map));
  memcpy(&apm_converted, &apm_clone, sizeof(ap_memory_pc_t));
  endian_swap_apm(&apm_converted);
  if (message) {
    memcpy(packet.message, &apm_converted.message, sizeof(apm_converted.message));
    write(USB_CMD_PC_MESSAGE, sizeof(packet.extra));
  }
  if (settings) {
    memcpy(packet.extra, &apm_converted.settings, sizeof(apm_converted.settings));
    write(USB_CMD_PC_SETTINGS, sizeof(apm_converted.settings));
  }
  if (misc) {
    memcpy(packet.extra, &apm_converted.misc, sizeof(apm_converted.misc));
    write(USB_CMD_PC_MISC, sizeof(apm_converted.misc));
  }
  if (items) {
    memcpy(packet.extra, &apm_converted.items, sizeof(apm_converted.items));
    write(USB_CMD_PC_ITEMS, sizeof(apm_converted.items));
  }
  if (traps) {
    memcpy(packet.extra, &apm_converted.traps, sizeof(apm_converted.traps));
    write(USB_CMD_PC_TRAPS, sizeof(apm_converted.traps));
  }
  if (exit_map) {
    int size = sizeof(ap_memory_pc_exit_map_t);
    int max = sizeof(packet.extra)/size;
    int n = 0;
    int offset = 0;
    for (int i = 0; i < AP_MEMORY_EXIT_MAP_MAX; i++) {
      memcpy(packet.extra+size*n, &apm_converted.exit_map[i], size);
      if (n == max) {
        packet.exit_map.offset = offset;
        packet.exit_map.size = size*n;
        write(USB_CMD_PC_EXIT_MAP, packet.exit_map.size);
        n = 0;
        offset += size*n;
      }
      n++;
    }
    if (n) {
      packet.exit_map.offset = offset;
      packet.exit_map.size = size*n;
      write(USB_CMD_PC_EXIT_MAP, packet.exit_map.size);
    }
  }
}

void USBCom::endian_swap8(void *dest, int bits) {
  typedef union {
    struct {
      uint8_t bit7 : 1;
      uint8_t bit6 : 1;
      uint8_t bit5 : 1;
      uint8_t bit4 : 1;
      uint8_t bit3 : 1;
      uint8_t bit2 : 1;
      uint8_t bit1 : 1;
      uint8_t bit0 : 1;
    };
    uint8_t byte;
  } byte_t;
  byte_t* dst = (byte_t*)dest;
  byte_t src = *(byte_t*)dest;
  src.byte = src.byte << (8-bits);
  dst->bit7 = src.bit0;
  dst->bit6 = src.bit1;
  dst->bit5 = src.bit2;
  dst->bit4 = src.bit3;
  dst->bit3 = src.bit4;
  dst->bit2 = src.bit5;
  dst->bit1 = src.bit6;
  dst->bit0 = src.bit7;
}

uint8_t USBCom::endian_swap8(uint8_t dest, int bits) {
  endian_swap8(&dest, bits);
  return dest;
}

void USBCom::endian_swap16(void *dest) {
  uint8_t *dst = (uint8_t*)dest;
  uint16_t src = *(uint16_t*)dest;
  dst[0] = (src >> 8) & 0xFF;
  dst[1] = (src >> 0) & 0xFF;
}

void USBCom::endian_swap32(void *dest) {
  uint8_t *dst = (uint8_t*)dest;
  uint32_t src = *(uint32_t*)dest;
  dst[0] = (src >> 24) & 0xFF;
  dst[1] = (src >> 16) & 0xFF;
  dst[2] = (src >>  8) & 0xFF;
  dst[3] = (src >>  0) & 0xFF;
}

void USBCom::endian_swap_packet() {
  switch (packet.cmd) {
    case USB_CMD_HANDSHAKE:
      endian_swap16(&packet.handshake.version.major);
      break;
    case USB_CMD_PC_EXIT_MAP:
      endian_swap16(&packet.exit_map.offset);
      endian_swap16(&packet.exit_map.size);
      break;
  }
}

void USBCom::endian_swap_save(bt_save_flags_t* save) {
  for (int i = 0; i < sizeof(bt_save_flags_t); i++) endian_swap8(&((u8*)save)[i]);
  save->hfp_sabreman = endian_swap8(save->hfp_sabreman, 2);
  save->ccl_seed1 = endian_swap8(save->ccl_seed1, 3);
  save->klungo_potion_order = endian_swap8(save->klungo_potion_order, 3);
  save->mt_prison_code = endian_swap8(save->mt_prison_code, 2);
  save->jiggywiggy_completed_challenges = endian_swap8(save->jiggywiggy_completed_challenges, 4);
  save->tdl_hatched_big_girl = endian_swap8(save->tdl_hatched_big_girl, 2);
  save->jinjo_pattern = endian_swap8(save->jinjo_pattern, 6);
  save->jrl_locker_names = endian_swap8(save->jrl_locker_names, 7);
  save->ccl_mumbo_location = endian_swap8(save->ccl_mumbo_location, 2);
  save->tower_of_tragedy_round = endian_swap8(save->tower_of_tragedy_round, 4);
  save->trade_honey_b = endian_swap8(save->trade_honey_b, 3);
  save->ww_moggy_location = endian_swap8(save->ww_moggy_location, 2);
  save->ww_groggy_location = endian_swap8(save->ww_groggy_location, 2);
}

void USBCom::endian_swap_apm(ap_memory_pc_t* apm) {
  endian_swap32(&apm->settings.seed);
  for (int i = 0; i < sizeof(apm->settings.silo_requirements)/2; i++) {
    endian_swap16(&apm->settings.silo_requirements[i]);
  }
  for (int i = 0; i < AP_MEMORY_EXIT_MAP_MAX; i++) {
    ap_memory_pc_exit_map_t* map = &apm->exit_map[i];
    endian_swap16(&map->on_map);
    endian_swap16(&map->og_map);
    endian_swap16(&map->to_map);
  }
}

void USBCom::log(const char* str, ...) {
  if (!USB_COM_LOGGING) return;
  va_list args;
  va_start(args, str);
  vprintf(str, args);
  va_end(args);
}
