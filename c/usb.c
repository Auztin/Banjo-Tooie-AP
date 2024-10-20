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
            usb.ping_frame = main.frame_count;
            usb_write(USB_CMD_PING, 0);
            break;
          }
        }
        if (!main.frame_count && ed64_can_write()) {
          memcpy(usb.packet.handshake.msg, "HELO", 4);
          usb.packet.handshake.version = USB_VERSION;
          usb_write(USB_CMD_HANDSHAKE, 4);
        }
        break;
      }
      case USB_STATUS_CONNECTING: {
        if (main.frame_count == usb.ping_frame) usb.status = USB_STATUS_DISCONNECTED;
        else if (ed64_can_read()) {
          usb_read();
          if (usb.packet.cmd == USB_CMD_PONG) usb.status = USB_STATUS_CONNECTED;
        }
        break;
      }
      case USB_STATUS_CONNECTED: {
        if (main.frame_count == usb.ping_frame) {
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
              usb.status ^= USB_STATUS_PINGED;
              usb.ping_frame = main.frame_count;
              break;
            }
            case USB_CMD_READ8: {
              usb.packet.mem.val = *(vu8*)usb.packet.mem.addr;
              usb_write(USB_CMD_READ8, 4);
              break;
            }
            case USB_CMD_READ16: {
              usb.packet.mem.val = *(vu16*)usb.packet.mem.addr;
              usb_write(USB_CMD_READ16, 4);
              break;
            }
            case USB_CMD_READ32: {
              usb.packet.mem.val = *(vu32*)usb.packet.mem.addr;
              usb_write(USB_CMD_READ32, 4);
              break;
            }
            case USB_CMD_WRITE8: {
              *(vu8*)usb.packet.mem.addr = usb.packet.mem.val;
              break;
            }
            case USB_CMD_WRITE16: {
              *(vu16*)usb.packet.mem.addr = usb.packet.mem.val;
              break;
            }
            case USB_CMD_WRITE32: {
              *(vu32*)usb.packet.mem.addr = usb.packet.mem.val;
              break;
            }
          }
        }
        break;
      }
    }
  }
}
