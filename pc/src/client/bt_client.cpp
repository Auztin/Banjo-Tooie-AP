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
        printf("Encoding getSlot");
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
auto self(shared_from_this());
json recv;
asio::streambuf buf;
asio::async_read_until(socket_, buf, "\n", 
    [this, self](std::error_code ec, std::size_t length)
{
    if(!ec)
    {
        printf("HI!\n");
    }
});
// socket_.async_read_some(asio::buffer(data_, max_length),
//     [this, self](std::error_code ec, std::size_t length)
//     {
//         if (!ec)
//         {
//             BTClient::do_write(length);
//         }
//     });
// std::istream is(&buf);
// std::string line;
// std::getline(is, line);
 recv = {};
 return recv;
}

void BTClient::send(std::string jsonData)
{
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(jsonData, jsonData.length()),
        [this, self](std::error_code ec, std::size_t /*length*/){});
}