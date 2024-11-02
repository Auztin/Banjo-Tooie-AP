
#include "server.hpp"

using asio::ip::tcp;
using std::string;

Server::Server(asio::io_context& io_context): acceptor_(io_context, tcp::endpoint(tcp::v4(), asio::ip::port_type(21221)))
{
    do_accept();
}

void Server::do_accept()
{
    acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<BTClient>(std::move(socket))->startLoop();
          }
          do_accept();
        });
}




