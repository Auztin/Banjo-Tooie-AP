#ifndef BT_CLIENT_HPP
#define BT_CLIENT_HPP

#include <asio.hpp>
#include <asio/awaitable.hpp>
#include <json.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

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
  const std::string CPP_VERSION = "V3.3.3"; //Make sure this matches with the BT_Client Version
  const std::string STATE_OK = "Ok";
  const std::string STATE_TENTATIVELY_CONNECTED = "Tentatively Connected";
  const std::string STATE_INITIAL_CONNECTION_MADE = "Initial Connection Made";
  const std::string STATE_UNINITIALIZED = "Uninitialized";
  int FRAME = 0;
  std::string CUR_STATE = STATE_UNINITIALIZED;
  std::string PREV_STATE = "";
  std::string PLAYER = "";
  bool DEATH_LINK = false;
  bool SKIP_TOT = false;
  bool ENABLE_AP_BK_MOVES = false;
  bool ENABLE_AP_CHEATO_REWARDS = false;
  bool ENABLE_AP_HONEYB_REWARDS = false;
  std::string MINIGAMES = "";
  bool SKIP_PUZZLES = false;
  bool SKIP_KLUNGO = false;
  bool OPEN_HAG1 = false;
  bool ENABLE_AP_CHUFFY = false;
  bool ENABLE_AP_WORLDS = false; //Used to Randomize World Order
  bool ENABLE_AP_MYSTERY = false; //StopNSwap
  int GOAL_TYPE = 0;
  int MGH_LENGTH = 0; //Mini-game Mumbo Token Length
  int BH_LENGTH = 0; //Boss Token Length
  int JFR_LENGTH = 0; //Jinjo Token Length
  int TH_LENGTH = 0; //Token Hunt Length
  std::string OPEN_SILO = "NONE"; //Which Silo is Open
  std::string CLIENT_VERSION = "V0.0";
  bool VERSION_ERR = false;

  int SEED = 0;
  asio::awaitable<void> receive();
  asio::awaitable<void> getSlotData();
  bool DEBUG_NET = false;
  asio::awaitable<void> send(std::string jsonData);
  asio::awaitable<nlohmann::json> read();
  void printGoalInfo();
};

#endif // BT_CLIENT_HPP
