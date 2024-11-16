#include <asio.hpp>

#include "client/bt_client.hpp"
#include "usb/usb_com.hpp"

int main() {
  asio::io_context io_context;
  BTClient bt_client(&io_context);
  USBCom usb_com(&io_context, &bt_client);
  io_context.run();
  return 0;
}
