#ifndef BT_CLIENT_HPP
#define BT_CLIENT_HPP

#include <asio.hpp>
#include <asio/awaitable.hpp>
#include <json.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include "data_map.hpp"



class BTClient {
public:
  const std::string STATE_OK = "Ok";
  const std::string STATE_TENTATIVELY_CONNECTED = "Tentatively Connected";
  const std::string STATE_INITIAL_CONNECTION_MADE = "Initial Connection Made";
  const std::string STATE_UNINITIALIZED = "Uninitialized";

  BTClient(asio::io_context*);
  std::string get_state();
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
  const int SCRIPT_VERSION = 4;
  std::string CPP_VERSION; // set using AP_VERSION from archipelago.h
  int FRAME = 0;
  std::string CUR_STATE = STATE_UNINITIALIZED;
  std::string PREV_STATE = "";

  /* Banjo-Tooie AP Settings */
  std::string PLAYER = "";
  int SEED = 0;
  u16 CURRENT_MAP = 0;
  bool DEATH_LINK = false;
  bool DEATH_LINK_TRIGGERED = false;
  int SKIP_TOT = 0;
  int ENABLE_AP_BK_MOVES = 0;
  bool ENABLE_AP_CHEATO_REWARDS = false;
  bool ENABLE_AP_HONEYB_REWARDS = false;
  bool MINIGAMES = false;
  bool SKIP_PUZZLES = false;
  bool BACKDOORS = false;
  bool SKIP_KLUNGO = false;
  bool OPEN_HAG1 = false;
  bool ENABLE_AP_CHUFFY = false;
  bool ENABLE_AP_WORLDS = false; //Used to Randomize World Order
  bool ENABLE_AP_MYSTERY = false; //StopNSwap
  bool ENABLE_AP_NESTS = false;
  int GOAL_TYPE = 0;
  int MGH_LENGTH = 0; //Mini-game Mumbo Token Length
  int BH_LENGTH = 0; //Boss Token Length
  int JFR_LENGTH = 0; //Jinjo Token Length
  int TH_LENGTH = 0; //Token Hunt Length
  int DIALOG_CHARACTER = 110;
  std::string OPEN_SILO = "NONE"; //Which Silo is Open
  std::string CLIENT_VERSION = "V0.0";
  /* EO Banjo-Tooie AP Settings */

  bool VERSION_ERR = false;
  bool DEBUG_NET = false;
  bool SHOW_GOAL_INFO = false;
  std::map<int, int> receive_map;
  int TOTAL_JIGGIES = 0;
  int TOTAL_TREBLE = 0;
  int TOTAL_PAGES = 0;
  int TOTAL_HONEYCOMB = 0;
  int TOTAL_DOUBLOONS = 0;
  int TOTAL_NOTES = 0;
  int WHITE_JINJO = 0;
  int ORANGE_JINJO = 0;
  int YELLOW_JINJO = 0;
  int BROWN_JINJO = 0;
  int GREEN_JINJO = 0;
  int RED_JINJO = 0;
  int BLUE_JINJO = 0;
  int PURPLE_JINJO = 0;
  int BLACK_JINJO = 0;
  int MUMBO_TOKENS = 0;

  std::map<std::string, int> WORLD_TABLE;
  std::map<std::string, std::string> RANDOM_ENTRANCES;
  typedef struct {
    int character;
    std::string text;
  } message_t;
  std::queue<message_t> MESSAGE_QUEUE;


  asio::awaitable<void> receive();
  asio::awaitable<void> getSlotData();
  asio::awaitable<void> send(std::string);
  asio::awaitable<nlohmann::json> read();
  void printGoalInfo();
  asio::awaitable<void> sendToBTClient();
  void process_block(nlohmann::json);
  void process_messages(std::string);
  void processAGIItem(nlohmann::json);
  void initialize_bt();
  nlohmann::json check_jiggy_locations();
  void obtain_jiggy();
  nlohmann::json check_treble_locations();
  void obtain_treble();
  nlohmann::json check_roysten_locations();
  void obtain_roysten_moves(int);
  bool check_amaze_o_gaze_location();
  void obtain_amaze_o_gaze();
  bool check_roar_location();
  void obtain_roar();
  void world_order_cost(nlohmann::json, nlohmann::json);
  void silo_cost(nlohmann::json);
  nlohmann::json check_unlock_worlds();
  void unlock_world(int);
  void randomize_entrances(nlohmann::json);
  void show_message(int, nlohmann::json, bool=false);
  nlohmann::json check_page_locations();
  void obtain_pages();
  nlohmann::json check_cheato_locations();
  nlohmann::json check_honeycomb_locations();
  void obtain_honeycomb();
  nlohmann::json check_honeyb_locations();
  nlohmann::json check_glowbo_locations();
  void obtain_magic(int);
  nlohmann::json check_doubloon_locations();
  void obtain_doubloon();
  nlohmann::json check_notes_locations();
  void obtain_notes();
  void obtain_bass();
  nlohmann::json check_jiggy_chunks_locations();
  nlohmann::json check_dino_kids_locations();
  void obtain_bk_moves(int);
  void obtain_progressive_moves(int);
  nlohmann::json check_mystery_locations();
  void obtain_mystery_items(int);
  nlohmann::json check_station_locations();
  void obtain_stations(int);
  nlohmann::json check_chuffy_location();
  void obtain_chuffy();
  nlohmann::json check_jamjars_locations();
  void obtain_jamjar_moves(int);
  nlohmann::json check_jinjo_locations();
  nlohmann::json check_jinjo_family_locations();
  nlohmann::json check_nest_locations();
  void obtain_jinjos(int);
  void obtain_mumbo_token();
};

#endif // BT_CLIENT_HPP
