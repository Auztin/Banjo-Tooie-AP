#pragma once
#ifndef SERVER_H
    #define SERVER_H
    #include <stdio.h>
    #include <string.h>
    #include <iostream>
    #include "asio.hpp"
    #include "../client/bt_client.hpp"

    using asio::ip::tcp;
    using std::string;

    class Server {
        public:
            Server(asio::io_context& io_context);
        private:
            tcp::acceptor acceptor_;
            void do_accept();
    };
#endif
