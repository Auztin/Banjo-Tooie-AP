#include "usb.h"
#include "main.h"
#include "ed64.h"
#include "dma.h"
#include <string.h>

usb_t usb = {0, };
const uint32_t USB_VERSION = USB_CURRENT_VERSION;

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

void usb_check() {
  if (!main.is_emulator) {
    if (usb.frame_count++ >= 15) usb.frame_count = 0;
    switch (usb.status & ~USB_STATUS_PINGED) {
      case USB_STATUS_DISCONNECTED: {
        if (ed64_can_read()) {
          usb.packet.handshake.version = 0;
          usb_read();
          if (
            usb.packet.cmd == USB_CMD_HANDSHAKE
            && !memcmp(usb.packet.handshake.msg, "'LO!", 4)
            && usb.packet.handshake.version == USB_VERSION
          ) {
            usb.status = USB_STATUS_CONNECTING;
            usb.ping_frame = usb.frame_count;
            usb_write(USB_CMD_PING, 0);
            break;
          }
        }
        if (!usb.frame_count && ed64_can_write()) {
          memcpy(usb.packet.handshake.msg, "HELO", 4);
          usb.packet.handshake.version = USB_VERSION;
          usb_write(USB_CMD_HANDSHAKE, 4);
        }
        break;
      }
      case USB_STATUS_CONNECTING: {
        if (usb.frame_count == usb.ping_frame) usb.status = USB_STATUS_DISCONNECTED;
        else if (ed64_can_read()) {
          usb_read();
          if (usb.packet.cmd == USB_CMD_PONG) {
            usb.status = USB_STATUS_CONNECTED;
            ap_memory.n64.misc.death_link_us = 0;
            ap_memory.n64.misc.death_link_ap = 0;
            usb.send.misc = 1;
            usb.send.saves_real = 1;
            usb.send.saves_fake = 1;
          }
        }
        break;
      }
      case USB_STATUS_CONNECTED: {
        if (usb.frame_count == usb.ping_frame) {
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
              usb.ping_frame = usb.frame_count;
              break;
            }
            case USB_CMD_PC_MISC: {
              memcpy(&ap_memory.pc.misc, usb.packet.extra, usb.packet.size);
              break;
            }
            case USB_CMD_PC_SETTINGS: {
              memcpy(&ap_memory.pc.settings, usb.packet.extra, usb.packet.size);
              break;
            }
            case USB_CMD_PC_ITEMS: {
              memcpy(ap_memory.pc.items, usb.packet.extra, usb.packet.size);
              break;
            }
            case USB_CMD_PC_EXIT_MAP: {
              memcpy(ap_memory.pc.exit_map+usb.packet.exit_map.offset, usb.packet.exit_map.data, usb.packet.size);
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
        }
        break;
      }
    }
  }
}
