#ifndef BT_CLIENT_HPP
#define BT_CLIENT_HPP

#include <asio.hpp>
#include <asio/awaitable.hpp>
#include <json.hpp>

class BTClient {
public:
  BTClient(asio::io_context*);
private:
  asio::io_context* io_context;
  asio::ip::tcp::acceptor server;
  asio::steady_timer timer_receive;
  // asio::steady_timer timer_other; rename this
  asio::ip::tcp::socket socket_;
  asio::streambuf buffer;

  void accept();
  void disconnected();
  bool check_state();
  asio::awaitable<void> every_30frames();
  // // void every_5frames();

  const std::string STATE_OK = "Ok";
  const std::string STATE_TENTATIVELY_CONNECTED = "Tentatively Connected";
  const std::string STATE_INITIAL_CONNECTION_MADE = "Initial Connection Made";
  const std::string STATE_UNINITIALIZED = "Uninitialized";
  int FRAME = 0;
  std::string CUR_STATE = STATE_UNINITIALIZED;
  std::string PREV_STATE = "";
  std::string PLAYER = "";
  int SEED = 0;
  asio::awaitable<void> receive();
  asio::awaitable<void> getSlotData();
  bool DEBUG_NET = false;
  asio::awaitable<void> send(std::string jsonData);
  asio::awaitable<nlohmann::json> read();
};

#endif // BT_CLIENT_HPP
