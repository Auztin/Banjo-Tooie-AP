#include "bt_client.hpp"

using json = nlohmann::json;

BTClient::BTClient(tcp::socket socket): socket_(std::move(socket))
{
}

void BTClient::getSlotData()
{
    json retTable = {};
    retTable["getSlot"] = true;
    if(DEBUG_NET == true)
    {
        // printf("Encoding getSlot");
    }
    string msg = retTable.dump() + "\n";
    send(msg);
    json j = read();
}

void BTClient::receive()
{
    if(PLAYER == "" && SEED == 0)
    {
        getSlotData();
    }
}

void BTClient::startLoop()
{
  CUR_STATE = STATE_INITIAL_CONNECTION_MADE;
  printf("Initial Connection Made");
  DEBUG_NET = true;

  while(true) {
    FRAME = FRAME + 1;
    if(CUR_STATE != PREV_STATE) {
        PREV_STATE = CUR_STATE;
    }
    if(CUR_STATE == STATE_OK || CUR_STATE == STATE_INITIAL_CONNECTION_MADE || CUR_STATE == STATE_TENTATIVELY_CONNECTED)
    {
        if(FRAME % 10000 == 1)
        {
            receive();
        }
        if(FRAME % 5 == 1)
        {

        }
    }
  }
}


json BTClient::read()
{
    asio::streambuf buffer;
    asio::read_until(socket_, buffer, "\n");
    std::istream is(&buffer);
    std::string line;
    std::getline(is, line);
    std::cout << line << std::endl << std::endl;
    json recv = json::parse(line);
    return recv;
}

void BTClient::send(std::string jsonData)
{
    auto self(shared_from_this());
    asio::write(socket_, asio::buffer(jsonData, jsonData.length()));
}