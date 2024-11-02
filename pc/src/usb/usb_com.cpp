
#include "usb_com.hpp"

const uint32_t USB_VERSION = USB_CURRENT_VERSION;

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
