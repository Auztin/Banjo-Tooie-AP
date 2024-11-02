
#include "bt_client.hpp"

using asio::ip::tcp;
using std::string;

BT_Client::BT_Client(asio::io_context& io_context): acceptor_(io_context, tcp::endpoint(tcp::v4(), asio::ip::port_type(21221)))
{
    do_accept();
}

void BT_Client::do_accept()
{
    acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
}


session::session(tcp::socket socket): socket_(std::move(socket))
{
}

void session::start()
{
  do_read();
}


void session::do_read()
{
auto self(shared_from_this());
socket_.async_read_some(asio::buffer(data_, max_length),
    [this, self](std::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            session::do_write(length);
        }
    });
}

void session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
}

