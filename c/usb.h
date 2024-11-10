#ifndef USB_H
#define USB_H

#include "util.h"
#include "usb_util.h"

enum USB_STATUS {
  USB_STATUS_DISCONNECTED   = 0,
  USB_STATUS_CONNECTING     = 1,
  USB_STATUS_CONNECTED      = 2,
  USB_STATUS_PINGED         = 4,
};

typedef struct {
  usb_packet_t packet;
  struct {
    u8 saves_real : 1;
    u8 saves_fake : 1;
    u8 misc : 1;
  } send;
  u8 status;
  u8 ping_frame;
} usb_t;
extern usb_t usb;

void usb_init();
void usb_check();

#endif // USB_H
