#ifndef USB_COM_HPP
#define USB_COM_HPP

#include <asio.hpp>
#include "usb_util.h"
#include "ftd2xx.h"
#include <archipelago.h>

#define USB_COM_LOGGING false

extern ap_memory_t ap_memory;
class BTClient;

class USBCom {
public:
  USBCom(asio::io_context*, BTClient*);
private:
  asio::steady_timer timer;
  asio::steady_timer timer_ping;
  FT_HANDLE handle;
  u8 status = USB_STATUS_DISCONNECTED;
  usb_packet_t packet = {0, };
  ap_memory_pc_t apm_clone = {0, };
  ap_memory_pc_t apm_converted = {0, };
  BTClient* bt_client;

  void check();
  void ping(bool check);
  FT_STATUS open();
  FT_STATUS read();
  FT_STATUS write(uint16_t cmd, uint16_t len);
  void process();
  bool check_changes(void* _real, void* _clone, int size);
  void send();
  void endian_swap8(void *dest, int bits=8);
  uint8_t endian_swap8(uint8_t dest, int bits=8);
  void endian_swap16(void *val);
  void endian_swap32(void *val);
  void endian_swap_packet();
  void endian_swap_save(bt_save_flags_t* save);
  void endian_swap_apm(ap_memory_pc_t* apm);
  void log(const char* str, ...);
};

#endif // USB_COM_HPP
