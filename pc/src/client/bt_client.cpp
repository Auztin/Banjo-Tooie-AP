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

nlohmann::json BTClient::check_jiggy_locations()
{
    nlohmann::json jiggy_check = {};
    u16 current_map = ap_memory.n64.misc.current_map;
    if(ASSET_MAP_CHECK.count(current_map))
    {
        if(ASSET_MAP_CHECK[current_map].count("JIGGIES"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[current_map]["JIGGIES"])
            {
                jiggy_check[locationId] = check_flag(locationId);
            }
        }
    }
    for(const std::string& locationId: ASSET_MAP_CHECK[0]["JIGGIES"])
    {
        jiggy_check[locationId] = check_flag(locationId);
    }
    return jiggy_check;
}

void BTClient::obtain_jiggy()
{
    TOTAL_JIGGIES++;
    ap_memory.pc.items[AP_ITEM_JIGGY] = TOTAL_JIGGIES;
    return;
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
    json block = co_await read();
    if(block.contains(string{"slot_player"}) && block["slot_player"] != "")
    {
        PLAYER = block["slot_player"];
        if(DEBUG_NET == true) { std::cout << "Player is: " << PLAYER << std::endl; }
    }
    if(block.contains(string{"slot_seed"}) && block["slot_seed"] != "")
    {
        SEED = block["slot_seed"];
        if(DEBUG_NET == true) { std::cout << "SEED is: " << SEED << std::endl; }
    }
    if(block.contains(string{"slot_deathlink"}) && block["slot_deathlink"] != "false")
    {
        DEATH_LINK = true;
        if(DEBUG_NET == true) { std::cout << "Deathlink is set" << std::endl; }
    }
    if(block.contains(string{"slot_skip_tot"}) && block["slot_skip_tot"] != "false")
    {
        SKIP_TOT = true;
        if(DEBUG_NET == true) { std::cout << "SKIP TOT is set" << std::endl; }
    }
    if(block.contains(string{"slot_bkmoves"}) && block["slot_bkmoves"] != "false")
    {
        ENABLE_AP_BK_MOVES = true;
        if(DEBUG_NET == true) { std::cout << "BK_MOVES is set" << std::endl; }
    }
    if(block.contains(string{"slot_cheatorewards"}) && block["slot_cheatorewards"] != "false")
    {
        ENABLE_AP_CHEATO_REWARDS = true;
        if(DEBUG_NET == true) { std::cout << "CHEATO_REWARDS is set" << std::endl; }
    }
    if(block.contains(string{"slot_honeybrewards"}) && block["slot_honeybrewards"] != "false")
    {
        ENABLE_AP_HONEYB_REWARDS = true;
        if(DEBUG_NET == true) { std::cout << "HONEYB_REWARDS is set" << std::endl; }
    }
    if(block.contains(string{"slot_minigames"}) && block["slot_minigames"] != "")
    {
        MINIGAMES = block["slot_minigames"];
        if(DEBUG_NET == true) { std::cout << "MINIGAMES set to " << MINIGAMES << std::endl; }
    }
    if(block.contains(string{"slot_skip_puzzles"}) && block["slot_skip_puzzles"] != "false")
    {
        SKIP_PUZZLES = true;
        if(DEBUG_NET == true) { std::cout << "SKIP_PUZZLES is set" << std::endl; }
    }
    if(block.contains(string{"slot_skip_klungo"}) && block["slot_skip_klungo"] != "false")
    {
        SKIP_KLUNGO = true;
        if(DEBUG_NET == true) { std::cout << "SKIP_KLUNGO is set" << std::endl; }
    }
    if(block.contains(string{"slot_open_hag1"}) && block["slot_open_hag1"] != "false")
    {
        OPEN_HAG1 = true;
        if(DEBUG_NET == true) { std::cout << "OPEN_HAG1 is set" << std::endl; }
    }
    if(block.contains(string{"slot_chuffy"}) && block["slot_chuffy"] != "false")
    {
        ENABLE_AP_CHUFFY = true;
        if(DEBUG_NET == true) { std::cout << "CHUFFY is set" << std::endl; }
    }
    if(block.contains(string{"slot_worlds"}) && block["slot_worlds"] != "false")
    {
        ENABLE_AP_WORLDS = true;
        if(DEBUG_NET == true) { std::cout << "Worlds are Shuffled" << std::endl; }
    }
    if(block.contains(string{"slot_mystery"}) && block["slot_mystery"] != "false")
    {
        ENABLE_AP_MYSTERY = true;
        if(DEBUG_NET == true) { std::cout << "StopNSwap is Randomized" << std::endl; }
    }
    if(block.contains(string{"slot_goal_type"}) && block["slot_goal_type"] != "")
    {
        GOAL_TYPE = block["slot_goal_type"];
        if(DEBUG_NET == true) { std::cout << "GOAL_TYPE is set to " << GOAL_TYPE << std::endl; }
    }
    if(block.contains(string{"slot_minigame_hunt_length"}) && block["slot_minigame_hunt_length"] != "")
    {
        MGH_LENGTH = block["slot_minigame_hunt_length"];
    }
    if(block.contains(string{"slot_boss_hunt_length"}) && block["slot_boss_hunt_length"] != "")
    {
        BH_LENGTH = block["slot_boss_hunt_length"];
    }
    if(block.contains(string{"slot_jinjo_family_rescue_length"}) && block["slot_jinjo_family_rescue_length"] != "")
    {
        JFR_LENGTH = block["slot_jinjo_family_rescue_length"];
    }
    if(block.contains(string{"slot_token_hunt_length"}) && block["slot_token_hunt_length"] != "")
    {
        TH_LENGTH = block["slot_token_hunt_length"];
    }
    if(block.contains(string{"slot_world_order"}))
    {
        // Here is you set Which Level to open in which order and set Jiggy Amount for each world.
        //slot_world_order is a Table.. Iterate in order using slot_keys. Below is the lua example:
        /*
            for level, jiggy_amt in pairs(block['slot_world_order'])
            do
                local locationId = block['slot_keys'][level]
                if level == "Outside Grunty's Industries"
                then
                    level = "Grunty Industries"
                elseif  level == "Jolly Roger's Lagoon - Town Center"
                then
                    level = "Jolly Roger's Lagoon"
                end
                for worlds, t in pairs(WORLD_ENTRANCE_MAP)
                do
                    if t['defaultName'] == level
                    then
                        WORLD_ENTRANCE_MAP[worlds]["defaultCost"] = jiggy_amt
                        WORLD_ENTRANCE_MAP[worlds]["locationId"] = tostring(locationId)
                    end
                end
            end
        */
    }
    if(block.contains(string{"slot_open_silo"}))
    {
        OPEN_SILO = block["slot_open_silo"];
    }
    if(block.contains(string{"slot_version"}) && block["slot_version"] != "")
    {
        CLIENT_VERSION = block["slot_version"];
        if(CLIENT_VERSION != CPP_VERSION)
        {
            VERSION_ERR = true;
            co_return;
        }
    }
    if(block.contains(string{"slot_zones"}))
    {
        //This Contains a table of Which Loading Zones enter to Which Worlds.
        //This will later Exand to more maps, but for now, its just the Front Entrances
    }
    if(SEED != 0){
        printGoalInfo();
    }
    co_return;
}

void BTClient::printGoalInfo()
{
    std::vector<string> encouragement{
        " GUH-HUH!",
        " BREEE!",
        " EEKUM BOKUM!",
        " YEEHAW!",
        " JINJOO!!",
        " WAHEY!!!",
        " ROOOOO!!!",
        " OOMANAKA!!!"
    };
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(encouragement), std::end(encouragement), rng);
    // Shuffle the Encouragement and pick one.
    if(GOAL_TYPE == 0)
    {
        std::cout << "You need to hunt down Grunty in her HAG1" << std::endl;
        std::cout << "and put her back in the ground!" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 1 && MGH_LENGTH == 15)
    {
        std::cout << "You are hunting down all 15 of the Mumbo Tokens" << std::endl;
        std::cout << "found in Grunty's dastardly minigames! Good luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 1 && MGH_LENGTH < 15)
    {
        std::cout << "You are hunting for " << MGH_LENGTH << " Mumbo Tokens from" << std::endl;
        std::cout << "Grunty's dastardly minigames! Good luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 2 && BH_LENGTH == 8)
    {
        std::cout << "You are hunting down all 8 Mumbo Tokens from" << std::endl;
        std::cout << "each world boss! Good Luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 2 && BH_LENGTH < 8)
    {
        std::cout << "You are hunting for " << BH_LENGTH << " Mumbo Tokens from" << std::endl;
        std::cout << "the 8 world bosses! Good Luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 3 && JFR_LENGTH == 9)
    {
        std::cout << "You are trying to rescue all 9 Jinjo families and" << std::endl;
        std::cout << "retrieve their Mumbo Tokens! Good Luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 3 && JFR_LENGTH < 9)
    {
        std::cout << "You are trying to rescue " << JFR_LENGTH << " of the 9 Jinjo families" << std::endl;
        std::cout << "and retrieve their Mumbo Tokens! Good Luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 4)
    {
        std::cout << "You absolute mad lad! You're doing the Wonder Wing Challenge! Good Luck and" << std::endl;
    }
    else if(GOAL_TYPE == 5 && TH_LENGTH == 15)
    {
        std::cout << "You are trying to find all 15 of Mumbo's Tokens scattered" << std::endl;
        std::cout << "throughout the Isle of Hags! Good Luck and" << encouragement[0] << std::endl;
    }
    else if(GOAL_TYPE == 5 && TH_LENGTH < 15)
    {
        std::cout << "You are trying to find " << TH_LENGTH << " of the 15 of Mumbo Tokens" << std::endl;
        std::cout << "scattered throughout the Isle of Hags! Good Luck and" << encouragement[0] << std::endl;
    }
    return;
}

asio::awaitable<void> BTClient::receive()
{
    if(PLAYER == "" && SEED == 0)
    {
        co_await getSlotData();
    }
    co_await sendToBTClient();
    json bt_data = co_await read();
    process_block(bt_data);
    co_return;
}

void BTClient::process_block(json bt_data)
{
    if(!bt_data.contains(string{"items"}))
    {
        return;
    }
    if(bt_data.contains(string{"slot_player"}))
    {
        return;
    }
    if(bt_data["items"] != "")
    {
        processAGIItem(bt_data["items"]);
    }
    // if(bt_data.contains(string{"messages"}) && bt_data["messages"] != "")
    // {
    //     for(auto msg : bt_data["messages"])
    //     {
    //         MESSAGE_TABLE.push_back(msg);
    //     }
    // }
    if(bt_data.contains(string{"triggerDeath"}) && bt_data["triggerDeath"] == true && DEATH_LINK == true)
    {
        ap_memory.pc.misc.death_link_ap++;
    }
}

// void BTClient::process_messages(std::string messages)
// {
//   if not string.find(message, "%(found%)")
// }

void BTClient::processAGIItem(json item_data)
{
    for(auto& itemId : item_data)
    {
        switch((int) itemId)
        {
            case 1230515: obtain_jiggy(); break;
        }
    }
}

asio::awaitable<void> BTClient::sendToBTClient()
{
    bool dead = false;
    json retTable = {};
    if(ap_memory.pc.misc.death_link_us != ap_memory.n64.misc.death_link_us)
    {
        dead = true;
        ap_memory.pc.misc.death_link_us++;
    }
    retTable["scriptVersion"] = SCRIPT_VERSION;
    retTable["playerName"] = PLAYER;
    retTable["deathlinkActive"] = DEATH_LINK;
    retTable["jiggies"] = check_jiggy_locations();
    retTable["hag"] = (bool) ap_memory.n64.saves.real.ck_defeated_hag1;
    retTable["isDead"] = dead;
    retTable["DEMO"] = false;
    retTable["banjo_map"] = ap_memory.n64.misc.current_map;
    retTable["sync_ready"] = true;
    co_await send(retTable);
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
