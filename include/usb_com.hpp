#include "usb_util.h"
#include "ftd2xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

const uint32_t USB_VERSION = USB_CURRENT_VERSION;
struct {
  FT_HANDLE handle;
  usb_packet_t packet;
} usb = {.packet = {0, }};

void memcpy16(void *dest, uint16_t src);
void memcpy32(void *dest, uint32_t src);
void endian_swap16(void *val);
void endian_swap32(void *val);
void usb_packet_endian_swap();
uint8_t usb_read();
uint8_t usb_write(uint16_t cmd, uint16_t len);