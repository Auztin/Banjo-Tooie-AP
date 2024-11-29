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
  CPP_VERSION = "V"+std::to_string(AP_VERSION.major)+"."+std::to_string(AP_VERSION.minor);
  if (AP_VERSION.patch) CPP_VERSION += "."+std::to_string(AP_VERSION.patch);
  this->io_context = io_context;
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
  PLAYER = "";
  SEED = 0;
  if (socket_.is_open()) socket_.close();
  accept();
}

bool BTClient::check_state() {
  if(CUR_STATE != PREV_STATE) {
      PREV_STATE = CUR_STATE;
  }
  return CUR_STATE == STATE_OK || CUR_STATE == STATE_INITIAL_CONNECTION_MADE || CUR_STATE == STATE_TENTATIVELY_CONNECTED;
}

// ---------------- JIGGY ------------------

nlohmann::json BTClient::check_jiggy_locations()
{
    nlohmann::json jiggy_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("JIGGIES"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["JIGGIES"])
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

// -------------- TREBLE -------------------

nlohmann::json BTClient::check_treble_locations()
{
    nlohmann::json treble_check = json({});

    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("TREBLE"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["TREBLE"])
            {
                treble_check[locationId] = check_flag(locationId);
            }
        }
    }
    return treble_check;
}

void BTClient::obtain_treble()
{
    TOTAL_TREBLE++;
    ap_memory.pc.items[AP_ITEM_TREBLE] = TOTAL_TREBLE;
    return;
}

// --------------- ROYSTEN -----------------

nlohmann::json BTClient::check_roysten_locations()
{
    nlohmann::json roysten_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("ROYSTEN"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["ROYSTEN"])
            {
                roysten_check[locationId] = check_flag(locationId);
            }
        }
    }
    return roysten_check;
}

void BTClient::obtain_roysten_moves(int itemId)
{
    if(itemId == 1230831) //progressive water training
    {
        if(ap_memory.pc.items[AP_ITEM_DIVE] == 0)
        {
            obtain_bk_moves(1230810);
        }
        else if(ap_memory.pc.items[AP_ITEM_DAIR] == 0)
        {
            ap_memory.pc.items[AP_ITEM_DAIR] = 1;
        }
        else if(ap_memory.pc.items[AP_ITEM_FSWIM] == 0)
        {
            ap_memory.pc.items[AP_ITEM_FSWIM] = 1;
        }
    }
    else if(itemId == 1230777)
    {
        ap_memory.pc.items[AP_ITEM_FSWIM] = 1;
    }
    else if(itemId == 1230778)
    {
        ap_memory.pc.items[AP_ITEM_DAIR] = 1;
    }
    return;
}

// --------------- AMAZE-O-GAZE -------------

bool BTClient::check_amaze_o_gaze_location()
{
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("AMAZE"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["AMAZE"])
            {
                return check_flag(locationId);
            }
        }
    }
    return false;
}

void BTClient::obtain_amaze_o_gaze()
{
    ap_memory.pc.items[AP_ITEM_AMAZEOGAZE] = 1;
    return;
}

// --------------- ROAR -------------

bool BTClient::check_roar_location()
{
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("ROAR"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["ROAR"])
            {
                return check_flag(locationId);
            }
        }
    }
    return false;
}

void BTClient::obtain_roar()
{
    ap_memory.pc.items[AP_ITEM_ROAR] = 1;
    return;
}

// -------------- PAGES --------------------------

nlohmann::json BTClient::check_page_locations()
{
    nlohmann::json pages_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("PAGES"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["PAGES"])
            {
                pages_check[locationId] = check_flag(locationId);
            }
        }
    }
    return pages_check;
}

void BTClient::obtain_pages()
{
    TOTAL_PAGES++;
    ap_memory.pc.items[AP_ITEM_PAGES] = TOTAL_PAGES;
    return;
}

// ---------------- CHEATO REWARDS ---------------

nlohmann::json BTClient::check_cheato_locations()
{
    nlohmann::json cheato_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("CHEATOR"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["CHEATOR"])
            {
                cheato_check[locationId] = check_flag(locationId);
            }
        }
    }
    return cheato_check;
}

// ---------------- HONEYCOMBS --------------------

nlohmann::json BTClient::check_honeycomb_locations()
{
    nlohmann::json honeycomb_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("HONEYCOMB"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["HONEYCOMB"])
            {
                honeycomb_check[locationId] = check_flag(locationId);
            }
        }
    }
    return honeycomb_check;
}

void BTClient::obtain_honeycomb()
{
    TOTAL_HONEYCOMB++;
    ap_memory.pc.items[AP_ITEM_HONEY] = TOTAL_HONEYCOMB;
    return;
}

// ------------- HONEYB --------------------------

nlohmann::json BTClient::check_honeyb_locations()
{
    nlohmann::json honeyb_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("HONEYB"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["HONEYB"])
            {
                honeyb_check[locationId] = check_flag(locationId);
            }
        }
    }
    return honeyb_check;
}

// ------------- Magic and Glowbos ---------------

nlohmann::json BTClient::check_glowbo_locations()
{
    nlohmann::json glowbo_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("GLOWBO"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["GLOWBO"])
            {
                glowbo_check[locationId] = check_flag(locationId);
            }
        }
    }
    return glowbo_check;
}

void BTClient::obtain_magic(int itemId)
{
    switch(itemId) {
        case 1230855: ap_memory.pc.items[AP_ITEM_MUMBOMT] = 1; break;
        case 1230856: ap_memory.pc.items[AP_ITEM_MUMBOGM] = 1; break;
        case 1230857: ap_memory.pc.items[AP_ITEM_MUMBOWW] = 1; break;
        case 1230858: ap_memory.pc.items[AP_ITEM_MUMBOJR] = 1; break;
        case 1230859: ap_memory.pc.items[AP_ITEM_MUMBOTD] = 1; break;
        case 1230860: ap_memory.pc.items[AP_ITEM_MUMBOGI] = 1; break;
        case 1230861: ap_memory.pc.items[AP_ITEM_MUMBOHP] = 1; break;
        case 1230862: ap_memory.pc.items[AP_ITEM_MUMBOCC] = 1; break;
        case 1230863: ap_memory.pc.items[AP_ITEM_MUMBOIH] = 1; break;

        case 1230174: ap_memory.pc.items[AP_ITEM_HUMBAMT] = 1; break;
        case 1230175: ap_memory.pc.items[AP_ITEM_HUMBAGM] = 1; break;
        case 1230176: ap_memory.pc.items[AP_ITEM_HUMBAWW] = 1; break;
        case 1230177: ap_memory.pc.items[AP_ITEM_HUMBAJR] = 1; break;
        case 1230178: ap_memory.pc.items[AP_ITEM_HUMBATD] = 1; break;
        case 1230179: ap_memory.pc.items[AP_ITEM_HUMBAGI] = 1; break;
        case 1230180: ap_memory.pc.items[AP_ITEM_HUMBAHP] = 1; break;
        case 1230181: ap_memory.pc.items[AP_ITEM_HUMBACC] = 1; break;
        case 1230182: ap_memory.pc.items[AP_ITEM_HUMBAIH] = 1; break;
    }
    return;
}

// -------------- DOUBLOONS ----------------------

nlohmann::json BTClient::check_doubloon_locations()
{
    nlohmann::json doubloon_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("DOUBLOON"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["DOUBLOON"])
            {
                doubloon_check[locationId] = check_flag(locationId);
            }
        }
    }
    return doubloon_check;
}

void BTClient::obtain_doubloon()
{
    TOTAL_DOUBLOONS++;
    ap_memory.pc.items[AP_ITEM_DOUBLOON] = TOTAL_DOUBLOONS;
    return;
}

// -------------- NOTES --------------------------

nlohmann::json BTClient::check_notes_locations()
{
    nlohmann::json notes_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("NOTES"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["NOTES"])
            {
                notes_check[locationId] = check_flag(locationId);
            }
        }
    }
    return notes_check;
}

void BTClient::obtain_notes()
{
    TOTAL_NOTES++;
    ap_memory.pc.items[AP_ITEM_NOTE] = TOTAL_NOTES;
    return;
}

void BTClient::obtain_bass()
{
    TOTAL_NOTES += 2;
    ap_memory.pc.items[AP_ITEM_NOTE] = TOTAL_NOTES;
    return;
}

// -------------- JIGGY CHUNKS -------------------

nlohmann::json BTClient::check_jiggy_chunks_locations()
{
    nlohmann::json chunks_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("CHUNKS"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["CHUNKS"])
            {
                chunks_check[locationId] = check_flag(locationId);
            }
        }
    }
    return chunks_check;
}

//---------------- DINO KIDS ---------------------

nlohmann::json BTClient::check_dino_kids_locations()
{
    nlohmann::json dino_check = json({});
    dino_check["1231006"] = check_flag("1231006");
    dino_check["1231007"] = check_flag("1231007");
    dino_check["1231008"] = check_flag("1231008");

    return dino_check;
}

//--------------- BK MOVES -----------------------

void BTClient::obtain_bk_moves(int itemId)
{
    switch(itemId) {
        case 1230810: ap_memory.pc.items[AP_ITEM_DIVE] = 1; break;
        case 1230811: ap_memory.pc.items[AP_ITEM_FPAD] = 1; break;
        case 1230812: ap_memory.pc.items[AP_ITEM_FFLIP] = 1; break;
        case 1230813: ap_memory.pc.items[AP_ITEM_EGGSHOOT] = 1; break;
        case 1230814: ap_memory.pc.items[AP_ITEM_ROLL] = 1; break;
        case 1230815: ap_memory.pc.items[AP_ITEM_TTROT] = 1; break;
        case 1230816: ap_memory.pc.items[AP_ITEM_TJUMP] = 1; break;
        case 1230817: ap_memory.pc.items[AP_ITEM_CLIMB] = 1; break;
        case 1230818: ap_memory.pc.items[AP_ITEM_FLUTTER] = 1; break;
        case 1230819: ap_memory.pc.items[AP_ITEM_WWING] = 1; break;
        case 1230820: ap_memory.pc.items[AP_ITEM_BBUST] = 1; break;
        case 1230821: ap_memory.pc.items[AP_ITEM_TTRAIN] = 1; break;
        case 1230822: ap_memory.pc.items[AP_ITEM_ARAT] = 1; break;
        case 1230823: ap_memory.pc.items[AP_ITEM_BEGGS] = 1; break;
        case 1230824: ap_memory.pc.items[AP_ITEM_GRAT] = 1; break;
        case 1230825: ap_memory.pc.items[AP_ITEM_BBARGE] = 1; break;
        case 1230826: ap_memory.pc.items[AP_ITEM_SSTRIDE] = 1; break;
        case 1230827: ap_memory.pc.items[AP_ITEM_BBOMB] = 1; break;
    }
    return;
}

// -------------- PROGRESSIVE ITEMS ---------------

void BTClient::obtain_progressive_moves(int itemId)
{
    if(itemId == 1230828) // Progressive Beak Buster
    {
        if(!ap_memory.pc.items[AP_ITEM_BBUST])
        {
            obtain_bk_moves(1230820);
        }
        else{
            ap_memory.pc.items[AP_ITEM_BDRILL] = 1;
        }
    }
    else if(itemId == 1230829) // Progressive Eggs
    {
        if(!ap_memory.pc.items[AP_ITEM_FEGGS])
        {
            ap_memory.pc.items[AP_ITEM_FEGGS] = 1;
        }
        else if(!ap_memory.pc.items[AP_ITEM_GEGGS])
        {
            ap_memory.pc.items[AP_ITEM_GEGGS] = 1;
        }
        else if(!ap_memory.pc.items[AP_ITEM_IEGGS])
        {
            ap_memory.pc.items[AP_ITEM_IEGGS] = 1;
        }
        else if(!ap_memory.pc.items[AP_ITEM_CEGGS])
        {
            ap_memory.pc.items[AP_ITEM_CEGGS] = 1;
        }
    }
    else if(itemId == 1230830) // Progressive Shoes
    {
        if(!ap_memory.pc.items[AP_ITEM_SSTRIDE])
        {
            obtain_bk_moves(1230826);
        }
        else if(!ap_memory.pc.items[AP_ITEM_TTRAIN])
        {
            obtain_bk_moves(1230821);
        }
        else if(!ap_memory.pc.items[AP_ITEM_SPRINGB])
        {
            ap_memory.pc.items[AP_ITEM_SPRINGB] = 1;
        }
        else if(!ap_memory.pc.items[AP_ITEM_CLAWBTS])
        {
            ap_memory.pc.items[AP_ITEM_CLAWBTS] = 1;
        }
    }
    else if(itemId == 1230831)
    {
        obtain_roysten_moves(itemId);
    }
    else if(itemId == 1230832)
    {
        if(!ap_memory.pc.items[AP_ITEM_GRAT])
        {
            obtain_bk_moves(1230824);
        }
        else if(!ap_memory.pc.items[AP_ITEM_BBASH])
        {
            ap_memory.pc.items[AP_ITEM_BBASH] = 1;
        }
    }
    return;
}

// -------------- STOP N SWAP --------------------

nlohmann::json BTClient::check_mystery_locations()
{
    nlohmann::json sns_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("STOPNSWAP"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["STOPNSWAP"])
            {
                sns_check[locationId] = check_flag(locationId);
            }
        }
    }
    return sns_check;
}

void BTClient::obtain_mystery_items(int itemId)
{
    switch(itemId)
    {
        case 1230799: ap_memory.pc.items[AP_ITEM_IKEY] = 1; break;
        case 1230800: ap_memory.pc.items[AP_ITEM_BBASH] = 1; break;
        case 1230801: /*message that they received Jinjo Multiplayer*/ break;
        case 1230802: ap_memory.pc.items[AP_ITEM_HOMINGEGGS] = 1; break;
        case 1230803: ap_memory.pc.items[AP_ITEM_BMEGG] = 1; break;
        case 1230804: ap_memory.pc.items[AP_ITEM_PMEGG] = 1; break;
    }
}

// -------------- STATIONS -----------------------

nlohmann::json BTClient::check_station_locations()
{
    nlohmann::json station_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("STATIONBTN"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["STATIONBTN"])
            {
                station_check[locationId] = check_flag(locationId);
            }
        }
    }
    return station_check;
}

void BTClient::obtain_stations(int itemId)
{
    switch(itemId)
    {
        case 1230790: ap_memory.pc.items[AP_ITEM_TRAINSWGI] = 1; break;
        case 1230791: ap_memory.pc.items[AP_ITEM_TRAINSWTD] = 1; break;
        case 1230792: ap_memory.pc.items[AP_ITEM_TRAINSWHP1] = 1; break;
        case 1230793: ap_memory.pc.items[AP_ITEM_TRAINSWHP2] = 1; break;
        case 1230794: ap_memory.pc.items[AP_ITEM_TRAINSWIH] = 1; break;
        case 1230795: ap_memory.pc.items[AP_ITEM_TRAINSWWW] = 1; break;
    }
}

// -------------- CHUFFY -------------------------

nlohmann::json BTClient::check_chuffy_location()
{
    nlohmann::json chuffy_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("CHUFFY"))
        {
            chuffy_check["1230796"] = check_flag("1230796");
        }
    }
    return chuffy_check;
}

void BTClient::obtain_chuffy()
{
    ap_memory.pc.items[AP_ITEM_CHUFFY] = 1;
    return;
}

// -------------- JAM JARS -----------------------

nlohmann::json BTClient::check_jamjars_locations()
{
    nlohmann::json jamjars_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("SILO"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["SILO"])
            {
                jamjars_check[locationId] = check_flag(locationId);
            }
        }
    }
    return jamjars_check;
}

void BTClient::obtain_jamjar_moves(int itemId)
{
    switch(itemId)
    {
        case 1230753: ap_memory.pc.items[AP_ITEM_GGRAB] = 1; break;
        case 1230754: ap_memory.pc.items[AP_ITEM_BBLASTER] = 1; break;
        case 1230755: ap_memory.pc.items[AP_ITEM_EGGAIM] = 1; break;
        case 1230756: ap_memory.pc.items[AP_ITEM_FEGGS] = 1; break;
        case 1230757: ap_memory.pc.items[AP_ITEM_BDRILL] = 1; break;
        case 1230758: ap_memory.pc.items[AP_ITEM_BBAYONET] = 1; break;
        case 1230759: ap_memory.pc.items[AP_ITEM_GEGGS] = 1; break;
        case 1230760: ap_memory.pc.items[AP_ITEM_AIREAIM] = 1; break;
        case 1230761: ap_memory.pc.items[AP_ITEM_SPLITUP] = 1; break;
        case 1230762: ap_memory.pc.items[AP_ITEM_PACKWH] = 1; break;
        case 1230763: ap_memory.pc.items[AP_ITEM_IEGGS] = 1; break;
        case 1230764: ap_memory.pc.items[AP_ITEM_WWHACK] = 1; break;
        case 1230765: ap_memory.pc.items[AP_ITEM_TTORP] = 1; break;
        case 1230766: ap_memory.pc.items[AP_ITEM_AUQAIM] = 1; break;
        case 1230767: ap_memory.pc.items[AP_ITEM_CEGGS] = 1; break;
        case 1230768: ap_memory.pc.items[AP_ITEM_SPRINGB] = 1; break;
        case 1230769: ap_memory.pc.items[AP_ITEM_TAXPACK] = 1; break;
        case 1230770: ap_memory.pc.items[AP_ITEM_HATCH] = 1; break;
        case 1230771: ap_memory.pc.items[AP_ITEM_SNPACK] = 1; break;
        case 1230772: ap_memory.pc.items[AP_ITEM_LSPRING] = 1; break;
        case 1230773: ap_memory.pc.items[AP_ITEM_CLAWBTS] = 1; break;
        case 1230774: ap_memory.pc.items[AP_ITEM_SHPACK] = 1; break;
        case 1230775: ap_memory.pc.items[AP_ITEM_GLIDE] = 1; break;
        case 1230776: ap_memory.pc.items[AP_ITEM_SAPACK] = 1; break;
    }
}

// -------------- JINJOS -------------------------

nlohmann::json BTClient::check_jinjo_locations()
{
    nlohmann::json jinjo_check = json({});
    if(ASSET_MAP_CHECK.count(CURRENT_MAP))
    {
        if(ASSET_MAP_CHECK[CURRENT_MAP].count("JINJOS"))
        {
            for(const std::string& locationId: ASSET_MAP_CHECK[CURRENT_MAP]["JINJOS"])
            {
                jinjo_check[locationId] = check_flag(locationId);
            }
        }
    }
    return jinjo_check;
}

void BTClient::obtain_jinjos(int itemId)
{
    switch(itemId)
    {
        case 1230501: WHITE_JINJO++; ap_memory.pc.items[AP_ITEM_WJINJO] = WHITE_JINJO; break;
        case 1230502: ORANGE_JINJO++; ap_memory.pc.items[AP_ITEM_OJINJO] = ORANGE_JINJO; break;
        case 1230503: YELLOW_JINJO++; ap_memory.pc.items[AP_ITEM_YJINJO] = YELLOW_JINJO; break;
        case 1230504: BROWN_JINJO++; ap_memory.pc.items[AP_ITEM_BRJINJO] = BROWN_JINJO; break;
        case 1230505: GREEN_JINJO++; ap_memory.pc.items[AP_ITEM_GJINJO] = GREEN_JINJO; break;
        case 1230506: RED_JINJO++; ap_memory.pc.items[AP_ITEM_RJINJO] = RED_JINJO; break;
        case 1230507: BLUE_JINJO++; ap_memory.pc.items[AP_ITEM_BLJINJO] = BLUE_JINJO; break;
        case 1230508: PURPLE_JINJO++; ap_memory.pc.items[AP_ITEM_PJINJO] = PURPLE_JINJO; break;
        case 1230509: BLACK_JINJO++; ap_memory.pc.items[AP_ITEM_BKJINJO] = BLACK_JINJO; break;
    }
}

nlohmann::json BTClient::check_jinjo_family_locations()
{
    nlohmann::json jinjo_fam_check = json({});
    for(const std::string& locationId: ASSET_MAP_CHECK[0]["JINJO_FAMILY"])
    {
        jinjo_fam_check[locationId] = check_flag(locationId);
    }
    return jinjo_fam_check;
}

// -------------- MUMBO TOKENS -------------------

void BTClient::obtain_mumbo_token()
{
    MUMBO_TOKENS++;
    ap_memory.pc.items[AP_ITEM_MUMBOTOKEN] = MUMBO_TOKENS;
    if (GOAL_TYPE == 5 && MUMBO_TOKENS == TH_LENGTH) show_message({{"message","You have found enough Mumbo Tokens! Time to head home!"}});
    return;
}


// -------------- Game Function ------------------

void BTClient::initialize_bt()
{
    // Init BK Moves
    if(ENABLE_AP_BK_MOVES == 0)
    {
        ap_memory.pc.items[AP_ITEM_DIVE] = 1;
        ap_memory.pc.items[AP_ITEM_FPAD] = 1;
        ap_memory.pc.items[AP_ITEM_GRAT] = 1;
        ap_memory.pc.items[AP_ITEM_ROLL] = 1;
        ap_memory.pc.items[AP_ITEM_ARAT] = 1;
        ap_memory.pc.items[AP_ITEM_BBARGE] = 1;
        ap_memory.pc.items[AP_ITEM_TJUMP] = 1;
        ap_memory.pc.items[AP_ITEM_FLUTTER] = 1;
        ap_memory.pc.items[AP_ITEM_FFLIP] = 1;
        ap_memory.pc.items[AP_ITEM_CLIMB] = 1;
        ap_memory.pc.items[AP_ITEM_BEGGS] = 1;
        ap_memory.pc.items[AP_ITEM_TTROT] = 1;
        ap_memory.pc.items[AP_ITEM_BBUST] = 1;
        ap_memory.pc.items[AP_ITEM_WWING] = 1;
        ap_memory.pc.items[AP_ITEM_SSTRIDE] = 1;
        ap_memory.pc.items[AP_ITEM_TTRAIN] = 1;
        ap_memory.pc.items[AP_ITEM_BBOMB] = 1;
        ap_memory.pc.items[AP_ITEM_EGGSHOOT] = 1;
    }
    else if(ENABLE_AP_BK_MOVES == 1)
    {
        ap_memory.pc.items[AP_ITEM_TJUMP] = 1;
        ap_memory.pc.items[AP_ITEM_TTROT] = 1;
    }
    // Skip Puzzles
    if(SKIP_PUZZLES == false)
    {
        ap_memory.pc.settings.jiggy_requirements[0] = 1;
        ap_memory.pc.settings.jiggy_requirements[1] = 4;
        ap_memory.pc.settings.jiggy_requirements[2] = 8;
        ap_memory.pc.settings.jiggy_requirements[3] = 14;
        ap_memory.pc.settings.jiggy_requirements[4] = 20;
        ap_memory.pc.settings.jiggy_requirements[5] = 28;
        ap_memory.pc.settings.jiggy_requirements[6] = 36;
        ap_memory.pc.settings.jiggy_requirements[7] = 45;
        ap_memory.pc.settings.jiggy_requirements[8] = 55;
        ap_memory.pc.settings.jiggy_requirements[9] = 70;
    }
    else
    {
        ap_memory.pc.settings.skip_puzzles = 1;
    }
    //HAG 1 Early
    if(OPEN_HAG1 == true && GOAL_TYPE != 4)
    {
        ap_memory.pc.items[AP_ITEM_H1A] = 1;
        show_message({{"message","HAG-1 is now open!"}});
    }
    else if(GOAL_TYPE != 4)
    {
        ap_memory.pc.settings.jiggy_requirements[9] = 70;
    }
    else
    {
        ap_memory.pc.settings.jiggy_requirements[9] = 99;
    }
    //KUNGO
    if(SKIP_KLUNGO == true)
    {
        ap_memory.pc.settings.skip_klungo = 1;
    }
    //CHUFFY
    if(ENABLE_AP_CHUFFY == true)
    {
        ap_memory.pc.settings.randomize_chuffy = 1;
    }
    //TOT
    ap_memory.pc.settings.skip_tower_of_tragedy = SKIP_TOT;
    //MINIGAME
    if(MINIGAMES == true)
    {
        ap_memory.pc.settings.speed_up_minigames = 1;
    }
    //SILO
    if(OPEN_SILO != "NONE")
    {
        if(OPEN_SILO == "ALL")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_WOODED_HOLLOW] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_PLATEAU] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_PINE_GROVE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_CLIFF_TOP] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_WASTELAND] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_QUAGMIRE] = 1;

        }
        else if(OPEN_SILO == "Isle O Hags - Plateau")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_PLATEAU] = 1;
        }
        else if(OPEN_SILO == "Isle O Hags - Plateau")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_PLATEAU] = 1;
        }
        else if(OPEN_SILO == "Isle O Hags - Pine Grove")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_PINE_GROVE] = 1;
        }
        else if(OPEN_SILO == "Isle O Hags - Cliff Top")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_CLIFF_TOP] = 1;
        }
        else if(OPEN_SILO == "Isle O Hags - Wasteland")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_WASTELAND] = 1;
        }
        else if(OPEN_SILO == "Isle O Hags - Quagmire")
        {
            ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE] = 1;
            ap_memory.pc.settings.open_silos[AP_SILO_QUAGMIRE] = 1;
        }
    }
    //Randomize World Entrances
}

void BTClient::world_order_cost(nlohmann::json world_order, nlohmann::json world_keys)
{
    for (auto& [world, cost] : world_order.items())
    {
        std::string locationId = std::to_string((int)world_keys[world]);
        WORLD_TABLE[locationId] = cost;
        if(world == "Mayahem Temple")
        {
            ap_memory.pc.settings.jiggy_requirements[0] = cost;
        }
        else if(world == "Glitter Gulch Mine")
        {
            ap_memory.pc.settings.jiggy_requirements[1] = cost;
        }
        else if(world == "Witchyworld")
        {
            ap_memory.pc.settings.jiggy_requirements[2] = cost;
        }
        else if(world == "Jolly Roger's Lagoon - Town Center")
        {
            ap_memory.pc.settings.jiggy_requirements[3] = cost;
        }
        else if(world == "Terrydactyland")
        {
            ap_memory.pc.settings.jiggy_requirements[4] = cost;
        }
        else if(world == "Outside Grunty Industries")
        {
            ap_memory.pc.settings.jiggy_requirements[5] = cost;
        }
        else if(world == "Hailfire Peaks")
        {
            ap_memory.pc.settings.jiggy_requirements[6] = cost;
        }
        else if(world == "Cloud Cuckooland")
        {
            ap_memory.pc.settings.jiggy_requirements[7] = cost;
        }
        else if(world == "Cauldron Keep")
        {
            ap_memory.pc.settings.jiggy_requirements[8] = cost;
        }
    }
}

nlohmann::json BTClient::check_unlock_worlds()
{
    nlohmann::json worlds_check = json({});
    for(auto& [locationId, cost] : WORLD_TABLE)
    {
        if(TOTAL_JIGGIES >= cost)
        {
            worlds_check[locationId] = true;
        }
    }
    if(GOAL_TYPE == 0 && TOTAL_JIGGIES >= 70 && OPEN_HAG1 == false)
    {
        ap_memory.pc.items[AP_ITEM_H1A] = 1;
        show_message({{"message","HAG-1 is now open!"}});
    }
    if(GOAL_TYPE == 4 && MUMBO_TOKENS == 32)
    {
        ap_memory.pc.items[AP_ITEM_H1A] = 1;
        show_message({{"message","HAG-1 is now open!"}});
    }
    return worlds_check;
}

void BTClient::unlock_world(int itemId)
{
    switch(itemId)
    {
        case 1230944: ap_memory.pc.items[AP_ITEM_MTA] = 1; break;
        case 1230945: ap_memory.pc.items[AP_ITEM_GGA] = 1; break;
        case 1230946: ap_memory.pc.items[AP_ITEM_WWA] = 1; break;
        case 1230947: ap_memory.pc.items[AP_ITEM_JRA] = 1; break;
        case 1230948: ap_memory.pc.items[AP_ITEM_TDA] = 1; break;
        case 1230949: ap_memory.pc.items[AP_ITEM_GIA] = 1; break;
        case 1230950: ap_memory.pc.items[AP_ITEM_HFA] = 1; break;
        case 1230951: ap_memory.pc.items[AP_ITEM_CCA] = 1; break;
        case 1230952: ap_memory.pc.items[AP_ITEM_CKA] = 1; break;
    }
}

void BTClient::randomize_entrances(json entrance_table)
{
    int i = 0;
    for(auto& [orig_world, new_world]: entrance_table.items())
    {
        if(orig_world == "Glitter Gulch Mine")
        {
            ap_memory.pc.exit_map[i].og_map = WORLD_ENTRANCES[orig_world].mapId;
            ap_memory.pc.exit_map[i].og_exit = 16;
            ap_memory.pc.exit_map[i].on_map = WORLD_ENTRANCES[orig_world].from_map;
            ap_memory.pc.exit_map[i].to_map = WORLD_ENTRANCES[new_world].mapId;
            ap_memory.pc.exit_map[i].to_exit = WORLD_ENTRANCES[new_world].entranceId;
            i++;
        }
        ap_memory.pc.exit_map[i].og_map = WORLD_ENTRANCES[orig_world].mapId;
        ap_memory.pc.exit_map[i].og_exit = WORLD_ENTRANCES[orig_world].entranceId;
        ap_memory.pc.exit_map[i].on_map = WORLD_ENTRANCES[orig_world].from_map;
        ap_memory.pc.exit_map[i].to_map = WORLD_ENTRANCES[new_world].mapId;
        ap_memory.pc.exit_map[i].to_exit = WORLD_ENTRANCES[new_world].entranceId;
        i++;

        ap_memory.pc.exit_map[i].og_map = WORLD_ENTRANCES[new_world].from_map;
        ap_memory.pc.exit_map[i].og_exit = WORLD_ENTRANCES[new_world].exitId;
        ap_memory.pc.exit_map[i].on_map = WORLD_ENTRANCES[new_world].mapId;
        ap_memory.pc.exit_map[i].to_map = WORLD_ENTRANCES[orig_world].from_map;
        ap_memory.pc.exit_map[i].to_exit = WORLD_ENTRANCES[orig_world].exitId;
        i++;
    }
}

void BTClient::show_message(json data) {
    std::string message;
    if (data.contains("message")) {
        message = data["message"];
        goto add_message;
    }
    if (!data.contains("item_id") || data["to_player"] != PLAYER) return;
    switch ((int)data["item_id"]) {
        case 1230753: // Grip Grab"
        case 1230754: // Breegull Blaster"
        case 1230755: // Egg Aim"
        case 1230757: // Bill Drill"
        case 1230758: // Beak Bayonet"
        case 1230760: // Airborne Egg Aiming"
        case 1230761: // Split Up"
        case 1230764: // Wing Whack"
        case 1230765: // Talon Torpedo"
        case 1230766: // Sub-Aqua Egg Aiming"
        case 1230774: // Shack Pack"
        case 1230775: // Glide"
        case 1230771: // Snooze Pack"
        case 1230772: // Leg Spring"
        case 1230773: // Claw Clamber Boots"
        case 1230768: // Springy Step Shoes"
        case 1230769: // Taxi Pack"
        case 1230770: // Hatch"
        case 1230762: // Pack Whack"
        case 1230776: // Sack Pack"
        case 1230777: // Fast Swimming"
        case 1230800: // Breegull Bash"
        case 1230802: // Homing Eggs Toggle"
        case 1230779: // Amaze-O-Gaze"
        case 1230780: // Baby T-Rex Roar"
        case 1230810: // Dive"
        case 1230811: // Flight Pad"
        case 1230824: // Ground Rat-a-tat Rap"
        case 1230814: // Roll"
        case 1230822: // Air Rat-a-tat Rap"
        case 1230825: // Beak Barge"
        case 1230816: // Tall Jump"
        case 1230818: // Flutter"
        case 1230812: // Flap Flip"
        case 1230817: // Climb"
        case 1230815: // Talon Trot"
        case 1230820: // Beak Buster"
        case 1230819: // Wonderwing"
        case 1230826: // Stilt Stride"
        case 1230821: // Turbo Trainers"
        case 1230827: // Beak Bomb"
        case 1230813: // Third Person Egg Shooting"
        case 1230855: // Mumbo: Golden Goliath"
        case 1230856: // Mumbo: Levitate"
        case 1230857: // Mumbo: Power"
        case 1230858: // Mumbo: Oxygenate"
        case 1230859: // Mumbo: Enlarge"
        case 1230860: // Mumbo: EMP"
        case 1230861: // Mumbo: Life Force"
        case 1230862: // Mumbo: Rain Dance"
        case 1230863: // Mumbo: Heal"
        case 1230174: // Humba: Stony"
        case 1230175: // Humba: Detonator"
        case 1230176: // Humba: Money Van"
        case 1230177: // Humba: Sub"
        case 1230178: // Humba: T-Rex"
        case 1230179: // Humba: Washing Machine"
        case 1230180: // Humba: Snowball"
        case 1230181: // Humba: Bee"
        case 1230182: // Humba: Dragon"
        case 1230794: // IoH: Train Station"
        case 1230791: // TDL: Train Station"
        case 1230790: // GI: Train Station"
        case 1230792: // HFP: Lava Side Train Station"
        case 1230793: // HFP: Icy Side Train Station"
        case 1230795: // WW: Train Station"
        case 1230796: // Chuffy"
        case 1230944: // Mayahem Temple"
        case 1230945: // Glitter Gulch Mine"
        case 1230946: // Witchyworld"
        case 1230947: // Jolly Roger's Lagoon"
        case 1230948: // Terrydactyland"
        case 1230949: // Grunty Industries"
        case 1230950: // Hailfire Peaks"
        case 1230951: // Cloud Cuckooland"
        case 1230952: // Cauldron Keep"
        case 1230828: // Progressive Beak Buster
        case 1230829: // Progressive Eggs
        case 1230830: // Progressive Shoes
        case 1230831: // Progressive Water Training
        case 1230832: // Progressive Bash Attack
            break;
        default: return;
    }
    if (data["player"] == PLAYER) message = "You have found your ";
    else message = string{data["player"]} + " sent your ";
    message += data["item"];
add_message:
    std::transform(message.begin(), message.end(), message.begin(), ::toupper);
    MESSAGE_QUEUE.push(message);
}

// -------------- Archipelago Function -----------
asio::awaitable<void> BTClient::getSlotData()
{
    json retTable = json({});
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
        ap_memory.pc.settings.seed = SEED;
        if(DEBUG_NET == true) { std::cout << "SEED is: " << SEED << std::endl; }
    }
    if(block.contains(string{"slot_deathlink"}) && block["slot_deathlink"] != "false")
    {
        DEATH_LINK = true;
        if(DEBUG_NET == true) { std::cout << "Deathlink is set" << std::endl; }
    }
    if(block.contains(string{"slot_skip_tot"}) && block["slot_skip_tot"] != "")
    {
        if(block["slot_skip_tot"] == "false")
        {
            SKIP_TOT = 0;
        }
        else if(block["slot_skip_tot"] == "true")
        {
            SKIP_TOT = 1;
        }
        else
        {
             SKIP_TOT = 2;
        }
        if(DEBUG_NET == true) { std::cout << "SKIP TOT is set" << std::endl; }
    }
    if(block.contains(string{"slot_bkmoves"}) && block["slot_bkmoves"] != "false")
    {
        ENABLE_AP_BK_MOVES = block["slot_bkmoves"];
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
    if(block.contains(string{"slot_minigames"}) && block["slot_minigames"] == "skip")
    {
        MINIGAMES = true;
        if(DEBUG_NET == true) { std::cout << "MINIGAMES is set" << std::endl; }
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
        world_order_cost(block["slot_world_order"], block["slot_keys"]);
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
        randomize_entrances(block["slot_zones"]);
    }
    if(SEED != 0){
        SHOW_GOAL_INFO = true;
        initialize_bt();
        if (CUR_STATE == STATE_INITIAL_CONNECTION_MADE) CUR_STATE = STATE_TENTATIVELY_CONNECTED;
    }
    co_return;
}

void BTClient::printGoalInfo()
{
    SHOW_GOAL_INFO = false;
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
        show_message({{"message","You need to hunt down Grunty in her HAG1 and put her back in the ground! " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 1 && MGH_LENGTH == 15)
    {
        show_message({{"message","You are hunting down all 15 of the Mumbo Tokens found in Grunty's dastardly minigames! Good luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 1 && MGH_LENGTH < 15)
    {
        show_message({{"message","You are hunting for " + std::to_string(MGH_LENGTH) + " Mumbo Tokens from Grunty's dastardly minigames! Good luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 2 && BH_LENGTH == 8)
    {
        show_message({{"message","You are hunting down all 8 Mumbo Tokens from each world boss! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 2 && BH_LENGTH < 8)
    {
        show_message({{"message","You are hunting for " + std::to_string(BH_LENGTH) + " Mumbo Tokens from the 8 world bosses! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 3 && JFR_LENGTH == 9)
    {
        show_message({{"message","You are trying to rescue all 9 Jinjo families and retrieve their Mumbo Tokens! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 3 && JFR_LENGTH < 9)
    {
        show_message({{"message","You are trying to rescue " + std::to_string(JFR_LENGTH) + " of the 9 Jinjo families and retrieve their Mumbo Tokens! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 4)
    {
        show_message({{"message","You absolute mad lad! You're doing the Wonder Wing Challenge! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 5 && TH_LENGTH == 15)
    {
        show_message({{"message","You are trying to find all 15 of Mumbo's Tokens scattered throughout the Isle of Hags! Good Luck and " + encouragement[0]}});
    }
    else if(GOAL_TYPE == 5 && TH_LENGTH < 15)
    {
        show_message({{"message","You are trying to find " + std::to_string(TH_LENGTH) + " of the 15 of Mumbo Tokens scattered throughout the Isle of Hags! Good Luck and " + encouragement[0]}});
    }
    return;
}

asio::awaitable<void> BTClient::receive()
{
    if(PLAYER == "" && SEED == 0)
    {
        co_await getSlotData();
    }
    else
    {
        co_await sendToBTClient();
        json bt_data = co_await read();
        process_block(bt_data);
    }
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
    if (CUR_STATE == STATE_TENTATIVELY_CONNECTED) CUR_STATE = STATE_OK;
    if(bt_data["items"] != "")
    {
        processAGIItem(bt_data["items"]);
    }
    if(bt_data.contains(string{"messages"}) && bt_data["messages"] != "")
    {
        for(auto msg : bt_data["messages"])
        {
            show_message(msg);
        }
    }
    if(bt_data.contains(string{"triggerDeath"}) && bt_data["triggerDeath"] == true && DEATH_LINK == true)
    {
        ap_memory.pc.misc.death_link_ap++;
    }
}

string BTClient::get_state()
{
    return CUR_STATE;
}

// void BTClient::process_messages(std::string messages)
// {
//   if not string.find(message, "%(found%)")
// }

void BTClient::processAGIItem(json item_data)
{
    for(int ap_id = 0; ap_id < item_data.size(); ap_id++)
    {
        auto itemId = item_data[ap_id];
        if (receive_map.count(ap_id)) continue;
        receive_map[ap_id] = itemId;
        //Mumbo and Humba Magic
        if((itemId >= 1230855 && itemId <= 1230863) || (itemId >= 1230174 && itemId <= 1230182))
        {
            obtain_magic(itemId);
        }
        else if((itemId >= 1230810 && itemId <= 1230827)) // BK Moves
        {
            obtain_bk_moves(itemId);
        }
        else if((itemId >= 1230828 && itemId <= 1230832)) // Progressive Moves
        {
            obtain_progressive_moves(itemId);
        }
        else if((itemId >= 1230799 && itemId <= 1230804)) // StopNSwap Items
        {
            obtain_mystery_items(itemId);
        }
        else if((itemId >= 1230790 && itemId <= 1230795)) // Station Items
        {
            obtain_stations(itemId);
        }
        else if((itemId >= 1230753 && itemId <= 1230776)) // Jamjar Moves
        {
            obtain_jamjar_moves(itemId);
        }
        else if((itemId >= 1230501 && itemId <= 1230509)) // Jinjos
        {
            obtain_jinjos(itemId);
        }
        else if((itemId >= 1230944 && itemId <= 1230952)) // Open World Entrances
        {
            unlock_world(itemId);
        }
        else // Everything else
        {
            switch((int) itemId)
            {
                case 1230512: obtain_honeycomb(); break;
                case 1230513: obtain_pages(); break;
                case 1230514: obtain_doubloon(); break;
                case 1230515: obtain_jiggy(); break;
                case 1230516: obtain_treble(); break;
                case 1230777: obtain_roysten_moves(1230777); break;
                case 1230778: obtain_roysten_moves(1230778); break;
                case 1230796: obtain_chuffy(); break;
                case 1230797: obtain_notes(); break;
                case 1230781: obtain_base(); break;
                case 1230831: obtain_roysten_moves(1230831); break;
                case 1230779: obtain_amaze_o_gaze(); break;
                case 1230780: obtain_roar(); break;
                case 1230798: obtain_mumbo_token(); break;
            }
        }
    }
}

asio::awaitable<void> BTClient::sendToBTClient()
{
    if (CURRENT_MAP != ap_memory.n64.misc.current_map) {
        CURRENT_MAP = ap_memory.n64.misc.current_map;
        if (CURRENT_MAP == 0x0158 && SEED != 0) SHOW_GOAL_INFO = true;
    }
    bool dead = false;
    json retTable = json({});
    if(ap_memory.pc.misc.death_link_us != ap_memory.n64.misc.death_link_us && DEATH_LINK && !DEATH_LINK_TRIGGERED)
    {
        dead = true;
        ap_memory.pc.misc.death_link_us++;
        DEATH_LINK_TRIGGERED = true;
    }
    else
    {
        DEATH_LINK_TRIGGERED = false;
    }
    retTable["scriptVersion"] = SCRIPT_VERSION;
    retTable["playerName"] = PLAYER;
    retTable["deathlinkActive"] = DEATH_LINK;
    retTable["jiggies"] = check_jiggy_locations();
    retTable["jinjos"] = check_jinjo_locations();
    retTable["pages"] = check_page_locations();
    retTable["honeycomb"] = check_honeycomb_locations();
    retTable["glowbo"] = check_glowbo_locations();
    retTable["doubloon"] = check_doubloon_locations();
    retTable["notes"] = check_notes_locations();
    retTable["hag"] = (bool) ap_memory.n64.saves.real.ck_defeated_hag1;
    retTable["unlocked_moves"] = check_jamjars_locations();
    retTable["treble"] = check_treble_locations();
    retTable["stations"] = check_station_locations();
    retTable["chuffy"] = check_chuffy_location();
    retTable["isDead"] = dead;
    retTable["jinjofam"] = check_jinjo_family_locations();
    retTable["worlds"] = check_unlock_worlds();
    retTable["mystery"] = check_mystery_locations();
    retTable["roysten"] = check_roysten_locations();
    retTable["cheato_rewards"] = check_cheato_locations();
    retTable["honeyb_rewards"] = check_honeyb_locations();
    retTable["jiggy_chunks"] = check_jiggy_chunks_locations();
    retTable["goggles"] = check_amaze_o_gaze_location();
    retTable["roar"] = check_roar_location();
    retTable["dino_kids"] = check_dino_kids_locations();
    retTable["DEMO"] = false;
    retTable["banjo_map"] = CURRENT_MAP;
    retTable["sync_ready"] = "true";

    co_await send(retTable.dump()+"\n");
    co_return;
}

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
    if (DEBUG_NET) std::cout << "[ IN] " << line << std::endl << std::endl;
    json recv = json::parse(line);

    co_return recv;
}

asio::awaitable<void> BTClient::send(std::string jsonData)
{
    if (DEBUG_NET) std::cout << "[OUT] " << jsonData << std::endl << std::endl;
    asio::error_code ec;
    co_await asio::async_write(socket_, asio::buffer(jsonData, jsonData.length()), asio::redirect_error(asio::use_awaitable, ec));
    if (ec) disconnected();
    co_return;
}


//------------------- Main Loop ---------------------

asio::awaitable<void> BTClient::every_30frames() {
  if (check_state()) {
    co_await receive();
  }
  if (SHOW_GOAL_INFO) printGoalInfo();
  if (ap_memory.n64.misc.current_map && ap_memory.n64.misc.show_message == ap_memory.pc.misc.show_message && !MESSAGE_QUEUE.empty()) {
    strcpy((char*)ap_memory.pc.message, MESSAGE_QUEUE.front().c_str());
    MESSAGE_QUEUE.pop();
    ap_memory.pc.misc.show_message++;
  }

  if(VERSION_ERR == true)
  {
    std::cout << "Error: Mismatch Version found... Please make sure your version matches." << std::endl;
    disconnected();
    VERSION_ERR = false;
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
