#include "bt_client.hpp"

#include <stdio.h>
#include <iostream>

#define BT_CLIENT_PORT 21221

using std::string;
using asio::ip::tcp;
using nlohmann::json;

BTClient::BTClient(asio::io_context* io_context):
  server(*io_context),
  socket_(*io_context),
  timer_receive(*io_context)/*,
  timer_other(io_context) */ {
  this->io_context = io_context;
  DEBUG_NET = true;
  printf("Starting server on port: %u\n", BT_CLIENT_PORT);
  tcp::endpoint endpoint(tcp::v4(), BT_CLIENT_PORT);
  server.open(endpoint.protocol());
  server.set_option(asio::socket_base::reuse_address(true));
  asio::error_code error;
  server.bind(endpoint, error);
  if (error) {
    printf("Error starting server: %s\n", error.message().c_str());
    return;
  }
  server.listen(1);
  accept();

  asio::co_spawn(*io_context, every_30frames(), asio::detached);
  // asio::co_spawn(*io_context, every_5frames(), asio::detached);
}

void BTClient::accept() {
  printf("Waiting for connection...\n");
  server.async_accept(socket_, [this](asio::error_code error){
    if (error) {
      printf("Error accepting connection: %s\n", error.message().c_str());
      return;
    }
    printf("Connection established!\n");
    CUR_STATE = STATE_INITIAL_CONNECTION_MADE;
  });
}

void BTClient::disconnected() {
  printf("Lost connection.\n");
  CUR_STATE = STATE_UNINITIALIZED;
  if (socket_.is_open()) socket_.close();
  accept();
}

bool BTClient::check_state() {
  if(CUR_STATE != PREV_STATE) {
      PREV_STATE = CUR_STATE;
  }
  return CUR_STATE == STATE_OK || CUR_STATE == STATE_INITIAL_CONNECTION_MADE || CUR_STATE == STATE_TENTATIVELY_CONNECTED;
}

asio::awaitable<void> BTClient::getSlotData()
{
    json retTable = {};
    retTable["getSlot"] = true;
    if(DEBUG_NET == true)
    {
        // printf("Encoding getSlot\n");
    }
    string msg = retTable.dump() + "\n";
    co_await send(msg);
    json j = co_await read();
    co_return;
}

asio::awaitable<void> BTClient::receive()
{
    if(PLAYER == "" && SEED == 0)
    {
        co_await getSlotData();
    }
    co_return;
}

asio::awaitable<void> BTClient::every_30frames() {
  if (check_state()) {
    co_await receive();
  }

  timer_receive.expires_after(std::chrono::milliseconds((int)(30/60.0*1000))); // every 30 frames if 60 fps
  timer_receive.async_wait([this](const asio::error_code& error) {
    if (error) printf("Error during 30 frame function: %s\n", error.message().c_str());
    else asio::co_spawn(*io_context, every_30frames(), asio::detached);
  });
  co_return;
}

// void BTClient::every_5frames() {
//   // TODO
// }

asio::awaitable<json> BTClient::read()
{
    asio::error_code ec;
    size_t size = co_await asio::async_read_until(socket_, buffer, "\n", asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
      disconnected();
      co_return json({});
    }
    std::string line(asio::buffer_cast<const char*>(buffer.data()), size);
    buffer.consume(size);
    std::cout << line << std::endl << std::endl;
    json recv = json::parse(line);

    co_return recv;
}

asio::awaitable<void> BTClient::send(std::string jsonData)
{
    asio::error_code ec;
    co_await asio::async_write(socket_, asio::buffer(jsonData, jsonData.length()), asio::redirect_error(asio::use_awaitable, ec));
    if (ec) disconnected();
    co_return;
}
