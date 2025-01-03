#ifndef USB_H
#define USB_H

#include "util.h"
#include "usb_util.h"

typedef struct {
  usb_packet_t packet;
  struct {
    u8 saves_real : 1;
    u8 saves_fake : 1;
    u8 saves_nests : 1;
    u8 misc : 1;
  } send;
  u8 status;
  s16 ping_timer;
} usb_t;
extern usb_t usb;

void usb_init();
void usb_check();

#endif // USB_H
