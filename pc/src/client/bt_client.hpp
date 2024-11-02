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
            BT_Client();
        private:
            string PREV_STATE = "";
            string CUR_STATE =  STATE_UNINITIALIZED;
            asio::io_context io_context;
            tcp::socket sock = tcp::socket(io_context);
    };
#endif

