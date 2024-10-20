#include "ftd2xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "usb_util.h"

const uint32_t USB_VERSION = USB_CURRENT_VERSION;
struct {
  FT_HANDLE handle;
  usb_packet_t packet;
} usb = {.packet = {0, }};

void memcpy16(void *dest, uint16_t src) {
  uint8_t *dst = (uint8_t*)dest;
  dst[0] = (src >> 8) & 0xFF;
  dst[1] = (src >> 0) & 0xFF;
}

void memcpy32(void *dest, uint32_t src) {
  uint8_t *dst = (uint8_t*)dest;
  dst[0] = (src >> 24) & 0xFF;
  dst[1] = (src >> 16) & 0xFF;
  dst[2] = (src >>  8) & 0xFF;
  dst[3] = (src >>  0) & 0xFF;
}

void endian_swap16(void *val) {
  memcpy16(val, *(uint16_t*)val);
}

void endian_swap32(void *val) {
  memcpy32(val, *(uint32_t*)val);
}

void usb_packet_endian_swap() {
  switch (usb.packet.cmd) {
    case USB_CMD_HANDSHAKE:
      endian_swap32(&usb.packet.handshake.version);
      break;
    case USB_CMD_READ8:
    case USB_CMD_READ16:
    case USB_CMD_READ32:
    case USB_CMD_WRITE8:
    case USB_CMD_WRITE16:
    case USB_CMD_WRITE32:
      endian_swap32(&usb.packet.mem.addr);
      endian_swap32(&usb.packet.mem.val);
      break;
  }
}

uint8_t usb_read() {
  DWORD size;
  if (FT_Read(usb.handle, usb.packet.raw, 8, &size) != FT_OK || size != 8) return 1;
  endian_swap16(&usb.packet.cmd);
  endian_swap16(&usb.packet.size);
  printf("[N64] cmd:%u size:%u data:0x", usb.packet.cmd, usb.packet.size);
  for (int i = 0; i < 4; i++) printf("%.2X", usb.packet.data[i]);
  if (usb.packet.size) {
    usb.packet.size--;
    usb.packet.size = usb.packet.size-usb.packet.size%4+4;
    if (usb.packet.size > 504) usb.packet.cmd = USB_CMD_NONE;
    else if (FT_Read(usb.handle, usb.packet.extra, usb.packet.size, &size) != FT_OK || size != usb.packet.size) return 1;
    printf(" extra:0x");
    for (int i = 0; i < size; i++) printf("%.2X", usb.packet.extra[i]);
  }
  printf("\n");
  usb_packet_endian_swap();
  return 0;
}

uint8_t usb_write(uint16_t cmd, uint16_t len) {
  DWORD size;
  if (len) {
    len--;
    len = len-len%4+4;
  }
  usb.packet.cmd = cmd;
  usb.packet.size = len;
  usb_packet_endian_swap();
  endian_swap16(&usb.packet.cmd);
  endian_swap16(&usb.packet.size);
  uint8_t ret = (FT_Write(usb.handle, usb.packet.raw, len+8, &size) != FT_OK || size != len+8) ? 1 : 0;
  printf("[ PC] cmd:%u size:%u data:0x", cmd, len);
  for (int i = 0; i < 4; i++) printf("%.2X", usb.packet.data[i]);
  if (len) {
    printf(" extra:0x", len);
    for (int i = 0; i < size-8; i++) printf("%.2X", usb.packet.extra[i]);
  }
  printf("\n");
  return ret;
}

int main() {
  uint8_t opened = 0;

  DWORD devices;
  FT_STATUS status = FT_CreateDeviceInfoList(&devices);
  if (status != FT_OK) return 1;
  if (devices) {
    FT_DEVICE_LIST_INFO_NODE dev_info[devices];
    status = FT_GetDeviceInfoList(dev_info, &devices);
    if (status != FT_OK) return 1;
    for (DWORD i = 0; i < devices; i++) {
      if (!strcmp(dev_info[i].Description, "FT245R USB FIFO") && dev_info[i].ID == 0x4036001) {
        if (FT_Open(i, &usb.handle) != FT_OK) return 1;
        opened = 1;
        FT_ResetDevice(usb.handle);
        FT_SetTimeouts(usb.handle, 0, 10000);
        FT_Purge(usb.handle, FT_PURGE_RX | FT_PURGE_TX);
      }
    }
  }
  if (!opened) return 1;

  while (1) {
    if (usb_read()) continue;
    switch (usb.packet.cmd) {
      case USB_CMD_HANDSHAKE: {
        printf("[N64] USB_CMD_HANDSHAKE\n");
        if (memcmp(usb.packet.handshake.msg, "HELO", 4)) {
          printf("USB Protocol invalid handshake message!\n");
          return 1;
        }
        if (usb.packet.handshake.version != USB_VERSION) {
          printf("USB Protocol version mismatch!\n");
          return 1;
        }
        memcpy(usb.packet.handshake.msg, "'LO!", 4);
        usb.packet.handshake.version = USB_VERSION;
        usb_write(USB_CMD_HANDSHAKE, 4);
        break;
      }
      case USB_CMD_PING: {
        printf("[N64] USB_CMD_PING\n");
        usb_write(USB_CMD_PONG, usb.packet.size);
        usb.packet.mem.addr = 0x8012C78D;
        usb_write(USB_CMD_READ8, 0);
        break;
      }
      case USB_CMD_READ8: {
        printf("[N64] USB_CMD_READ8 0x%.8X = 0x%X\n", usb.packet.mem.addr, usb.packet.mem.val);
        if (usb.packet.mem.addr == 0x8012C78D && usb.packet.mem.val == 0) {
          usb.packet.mem.addr = 0x8012C78D;
          usb.packet.mem.val = 0x40;
          usb_write(USB_CMD_WRITE8, 4);
        }
        break;
      }
    }
  }
  return 0;
}

// int main() {
//   printf("tiles %u\n", sizeof(tiles)/1024/1024);
//   printf("usb.packet %u %p\n", sizeof(usb.packet_t), &usb.packet);
//   printf("cmd %p\n", &usb.packet.cmd);
//   printf("size %p\n", &usb.packet.size);
//   printf("handshake %u %p\n", sizeof(usb.packet.handshake), &usb.packet.handshake);
//   printf("mem %u %p\n", sizeof(usb.packet.mem), &usb.packet.mem);
//   printf("data %p\n", &usb.packet.data);
//   printf("extra %p\n", &usb.packet.extra);
//   return 0;
// }
