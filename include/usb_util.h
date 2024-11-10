#ifndef USB_UTIL_H
#define USB_UTIL_H

#include <stdint.h>

extern const uint32_t USB_VERSION;
#define USB_CURRENT_VERSION 1

enum USB_CMD {
  USB_CMD_NONE,
  USB_CMD_HANDSHAKE,
  USB_CMD_PING,
  USB_CMD_PONG,
  USB_CMD_PC_MISC,
  USB_CMD_PC_SETTINGS,
  USB_CMD_PC_ITEMS,
  USB_CMD_PC_EXIT_MAP,
  USB_CMD_N64_MISC,
  USB_CMD_N64_SAVES_REAL,
  USB_CMD_N64_SAVES_FAKE,
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
          uint32_t offset;
          uint8_t data[504];
        } exit_map;
      };
    };
    uint8_t raw[512];
  };
} usb_packet_t;

#endif // USB_UTIL_H
