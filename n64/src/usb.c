#include "usb.h"
#include "main.h"
#include "ed64.h"
#include "dma.h"
#include <string.h>

usb_t usb = {0, };

void usb_init() {
  if (!main.is_emulator) ed64_init();
}

u8 usb_read() {
  if (ed64_read(usb.packet.raw, 8)) return 1;
  if (usb.packet.size) {
    usb.packet.size--;
    usb.packet.size = usb.packet.size-usb.packet.size%4+4;
    if (usb.packet.size > 504) usb.packet.cmd = USB_CMD_NONE;
    else if (ed64_read(usb.packet.extra, usb.packet.size)) return 1;
  }
  return 0;
}

u8 usb_write(u8 cmd, u32 len) {
  if (len) {
    len--;
    len = len-len%4+4;
  }
  usb.packet.cmd = cmd;
  usb.packet.size = len;
  u8 ret = ed64_write(usb.packet.raw, usb.packet.size+8);
  return ret;
}

void usb_apmemcpy(void* to, void* from, u32 size) {
  if ((u32)to < (u32)&ap_memory || (u32)(to+size) > (u32)(&ap_memory+sizeof(ap_memory))) {
    usb.status = USB_STATUS_DISCONNECTED;
    return;
  }
  memcpy(to, from, size);
}

void usb_check() {
  disable_interrupts();
  if (!main.is_emulator && !dma_busy()) {
    usb.ping_timer += main.delta;
    if (usb.ping_timer >= 500) usb.ping_timer = 0;
    switch (usb.status & ~USB_STATUS_PINGED) {
      case USB_STATUS_DISCONNECTED: {
        if (ed64_can_read()) {
          usb.packet.handshake.version.as_int = 0;
          usb_read();
          if (
            usb.packet.cmd == USB_CMD_HANDSHAKE
            && !memcmp(usb.packet.handshake.msg, "'LO!", 4)
            && usb.packet.handshake.version.as_int == AP_VERSION.as_int
          ) {
            usb.status = USB_STATUS_CONNECTING;
            usb_write(USB_CMD_PING, 0);
            break;
          }
        }
        if (!usb.ping_timer && ed64_can_write()) {
          memcpy(usb.packet.handshake.msg, "HELO", 4);
          usb.packet.handshake.version.as_int = AP_VERSION.as_int;
          usb_write(USB_CMD_HANDSHAKE, 4);
        }
        break;
      }
      case USB_STATUS_CONNECTING: {
        if (!usb.ping_timer) usb.status = USB_STATUS_DISCONNECTED;
        else if (ed64_can_read()) {
          usb_read();
          if (usb.packet.cmd == USB_CMD_PONG) {
            usb.status = USB_STATUS_CONNECTED;
            ap_memory.pc.misc.show_message = 0;
            ap_memory.pc.misc.death_link_us = 0;
            ap_memory.pc.misc.death_link_ap = 0;
            ap_memory.n64.misc.death_link_us = 0;
            ap_memory.n64.misc.death_link_ap = 0;
            ap_memory.n64.misc.show_message = 0;
            usb.send.misc = 1;
            usb.send.saves_real = 1;
            usb.send.saves_fake = 1;
            usb.send.saves_nests = 1;
          }
        }
        break;
      }
      case USB_STATUS_CONNECTED: {
        if (!usb.ping_timer) {
          if (usb.status & USB_STATUS_PINGED) {
            usb.status = USB_STATUS_DISCONNECTED;
            break;
          }
          usb_write(USB_CMD_PING, 0);
          usb.status |= USB_STATUS_PINGED;
        }
        while (ed64_can_read() && !usb_read()) {
          switch (usb.packet.cmd) {
            case USB_CMD_PING: {
              usb_write(USB_CMD_PONG, usb.packet.size);
              break;
            }
            case USB_CMD_PONG: {
              usb.status &= ~USB_STATUS_PINGED;
              usb.ping_timer = 0;
              break;
            }
            case USB_CMD_PC_MISC: {
              usb_apmemcpy(&ap_memory.pc.misc, usb.packet.extra, sizeof(ap_memory.pc.misc));
              break;
            }
            case USB_CMD_PC_MESSAGE: {
              usb_apmemcpy(&ap_memory.pc.message, usb.packet.message, sizeof(ap_memory.pc.message));
              break;
            }
            case USB_CMD_PC_SETTINGS: {
              usb_apmemcpy(&ap_memory.pc.settings, usb.packet.extra, sizeof(ap_memory.pc.settings));
              break;
            }
            case USB_CMD_PC_ITEMS: {
              usb_apmemcpy(ap_memory.pc.items, usb.packet.extra, sizeof(ap_memory.pc.items));
              break;
            }
            case USB_CMD_PC_TRAPS: {
              usb_apmemcpy(ap_memory.pc.traps, usb.packet.extra, sizeof(ap_memory.pc.traps));
              break;
            }
            case USB_CMD_PC_EXIT_MAP: {
              usb_apmemcpy(ap_memory.pc.exit_map+usb.packet.exit_map.offset, usb.packet.exit_map.data, usb.packet.exit_map.size);
              break;
            }
          }
        }
        if (BT_IN_GAME && ed64_can_write()) {
          u16 size;
          if (usb.send.misc) {
            size = sizeof(ap_memory.n64.misc);
            memcpy(usb.packet.extra, &ap_memory.n64.misc, size);
            if (!usb_write(USB_CMD_N64_MISC, size)) usb.send.misc = 0;
          }
          else if (usb.send.saves_real) {
            size = sizeof(bt_save_flags_t);
            memcpy(usb.packet.extra, &ap_memory.n64.saves.real, size);
            if (!usb_write(USB_CMD_N64_SAVES_REAL, size)) usb.send.saves_real = 0;
          }
          else if (usb.send.saves_fake) {
            size = sizeof(bt_save_flags_t);
            memcpy(usb.packet.extra, &ap_memory.n64.saves.fake, size);
            if (!usb_write(USB_CMD_N64_SAVES_FAKE, size)) usb.send.saves_fake = 0;
          }
          else if (usb.send.saves_nests) {
            size = sizeof(ap_memory.n64.saves.nests);
            memcpy(usb.packet.extra, &ap_memory.n64.saves.nests, size);
            if (!usb_write(USB_CMD_N64_SAVES_NESTS, size)) usb.send.saves_nests = 0;
          }
        }
        break;
      }
    }
  }
  enable_interrupts();
}
