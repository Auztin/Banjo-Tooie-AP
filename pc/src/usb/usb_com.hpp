#ifndef USB_COM_HPP
#define USB_COM_HPP

#include "usb_util.h"
#include "ftd2xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ap_memory.h>

extern ap_memory_t ap_memory;

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

#endif // USB_COM_HPP
