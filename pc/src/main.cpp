#include "json.hpp"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <asio.hpp>

#include "client/bt_client.hpp"
#include "usb/usb_com.hpp"


using json = nlohmann::json;


int main() {

  // json
  json j = {
    {"pi", 3.141},
    {"happy", true},
    {"name", "Niels"},
    {"nothing", nullptr},
    {"answer", {
      {"everything", 42}
    }},
    {"list", {1, 0, 2}},
    {"object", {
      {"currency", "USD"},
      {"value", 42.99}
    }}
  };

  j["answer"]["life"] = 42;
  j["answer"]["the_universe"] = "42";

  // std::cout << j["answer"]["everything"] << std::endl;
  // std::cout << j << std::endl;
  // std::cout << j.dump(4) << std::endl;

  asio::io_context io_context;
  BTClient bt_client(&io_context);
  io_context.run();
  return 0;

  uint8_t opened = 0;

  DWORD devices;
  FT_STATUS status = FT_CreateDeviceInfoList(&devices);
  if (status != FT_OK) return 1;
  if (devices) {
    FT_DEVICE_LIST_INFO_NODE dev_info[devices];
    status = FT_GetDeviceInfoList(dev_info, &devices);
    if (status != FT_OK) return 1;
    for (DWORD i = 0; i < devices; i++) {
      if (!strcmp(dev_info[i].Description, "FT245R USB FIFO") && dev_info[i].ID == 0x4036001) {
        if (FT_Open(i, &usb.handle) != FT_OK) return 1;
        opened = 1;
        FT_ResetDevice(usb.handle);
        FT_SetTimeouts(usb.handle, 0, 10000);
        FT_Purge(usb.handle, FT_PURGE_RX | FT_PURGE_TX);
      }
    }
  }
  if (!opened) return 1;

  while (1) {
    if (usb_read()) continue;
    switch (usb.packet.cmd) {
      case USB_CMD_HANDSHAKE: {
        printf("[N64] USB_CMD_HANDSHAKE\n");
        if (memcmp(usb.packet.handshake.msg, "HELO", 4)) {
          printf("USB Protocol invalid handshake message!\n");
          return 1;
        }
        if (usb.packet.handshake.version != USB_VERSION) {
          printf("USB Protocol version mismatch!\n");
          return 1;
        }
        memcpy(usb.packet.handshake.msg, "'LO!", 4);
        usb.packet.handshake.version = USB_VERSION;
        usb_write(USB_CMD_HANDSHAKE, 4);
        break;
      }
      case USB_CMD_PING: {
        printf("[N64] USB_CMD_PING\n");
        usb_write(USB_CMD_PONG, usb.packet.size);
        usb.packet.mem.addr = 0x8012C78D;
        usb_write(USB_CMD_READ8, 0);
        break;
      }
      case USB_CMD_READ8: {
        printf("[N64] USB_CMD_READ8 0x%.8X = 0x%X\n", usb.packet.mem.addr, usb.packet.mem.val);
        if (usb.packet.mem.addr == 0x8012C78D && usb.packet.mem.val == 0) {
          usb.packet.mem.addr = 0x8012C78D;
          usb.packet.mem.val = 0x40;
          usb_write(USB_CMD_WRITE8, 4);
        }
        break;
      }
    }
  }
  return 0;
}
