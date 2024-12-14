#ifndef USB_UTIL_H
#define USB_UTIL_H

#include <archipelago.h>

enum USB_STATUS {
  USB_STATUS_DISCONNECTED = 0,
  USB_STATUS_CONNECTING   = 1,
  USB_STATUS_CONNECTED    = 2,
  USB_STATUS_PINGED       = 4,
};

enum USB_CMD {
  USB_CMD_NONE,
  USB_CMD_HANDSHAKE,
  USB_CMD_PING,
  USB_CMD_PONG,
  USB_CMD_PC_MISC,
  USB_CMD_PC_MESSAGE,
  USB_CMD_PC_SETTINGS,
  USB_CMD_PC_ITEMS,
  USB_CMD_PC_TRAPS,
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
          ap_version_t version;
        } handshake;
        struct {
          uint16_t offset;
          uint16_t size;
          uint8_t data[504];
        } exit_map;
        uint8_t message[508];
      };
    };
    uint8_t raw[512];
  };
} usb_packet_t;

#endif // USB_UTIL_H
