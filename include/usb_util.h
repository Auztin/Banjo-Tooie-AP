#pragma once
#ifndef USB_UTIL_H
#define USB_UTIL_H

extern const uint32_t USB_VERSION;
#define USB_CURRENT_VERSION 1

enum USB_CMD {
  USB_CMD_NONE,
  USB_CMD_HANDSHAKE,
  USB_CMD_PING,
  USB_CMD_PONG,
  USB_CMD_READ8,
  USB_CMD_READ16,
  USB_CMD_READ32,
  USB_CMD_WRITE8,
  USB_CMD_WRITE16,
  USB_CMD_WRITE32,
  // USB_CMD_WATCH8,
  // USB_CMD_WATCH16,
  // USB_CMD_WATCH32,
  // USB_CMD_FORCE8,
  // USB_CMD_FORCE16,
  // USB_CMD_FORCE32,
};

typedef struct {
  union {
    struct {
      uint16_t cmd;
      uint16_t size;
      union {
        struct {
          uint8_t data[4];
          uint8_t extra[504];
        };
        struct {
          uint8_t msg[4];
          uint32_t version;
        } handshake;
        struct {
          uint32_t addr;
          uint32_t val;
        } mem;
      };
    };
    uint8_t raw[512];
  };
} usb_packet_t;

#endif // USB_UTIL_H
