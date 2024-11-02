#pragma once
#ifndef BT_H
    #define BT_H
    #include <stdio.h>
    #include <string.h>
    #include <iostream>
    #include "asio.hpp"
    #include "json.hpp"

    using asio::ip::tcp;
    using std::string;

    const std::string STATE_OK = "Ok";
    const std::string STATE_TENTATIVELY_CONNECTED = "Tentatively Connected";
    const std::string STATE_INITIAL_CONNECTION_MADE = "Initial Connection Made";
    const std::string STATE_UNINITIALIZED = "Uninitialized";

    class BTClient: public std::enable_shared_from_this<BTClient>
    {
        public:
            BTClient(tcp::socket socket);
            void startLoop();
        private:
            tcp::socket socket_;
            enum { max_length = 1024 };
            char data_[max_length];
            int FRAME = 0;
            std::string CUR_STATE = STATE_UNINITIALIZED;
            std::string PREV_STATE = "";
            std::string PLAYER = "";
            int SEED = 0;
            void receive();
            void getSlotData();
            bool DEBUG_NET = false;
            void send(std::string jsonData);
            nlohmann::json read();

    };
#endif