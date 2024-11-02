#pragma once
#ifndef BT_H
    #define BT_H
    #include <stdio.h>
    #include <string.h>
    #include <iostream>
    #include "asio.hpp"

    using asio::ip::tcp;
    using std::string;

    const std::string STATE_OK = "Ok";
    const std::string STATE_TENTATIVELY_CONNECTED = "Tentatively Connected";
    const std::string STATE_INITIAL_CONNECTION_MADE = "Initial Connection Made";
    const std::string STATE_UNINITIALIZED = "Uninitialized";

    class BT_Client {
        public:
            BT_Client(asio::io_context& io_context);
        private:
            string PREV_STATE = "";
            string CUR_STATE =  STATE_UNINITIALIZED;
            tcp::acceptor acceptor_;
            void do_accept();
    };

    class session: public std::enable_shared_from_this<session>
    {
        public:
            session(tcp::socket socket);
            void start();
            void do_read();
            void do_write(std::size_t length);
        private:
            tcp::socket socket_;
            enum { max_length = 1024 };
            char data_[max_length];
    };
#endif
