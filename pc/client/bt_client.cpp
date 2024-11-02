
#include "../../include/bt_client.hpp"
 
using asio::ip::tcp;
using std::string;

BT_Client::BT_Client() {
        try
        {
            tcp::resolver resolver(io_context);
            asio::connect(sock, resolver.resolve("127.0.0.1", "21221"));

            std::cout << "Sending: test" << std::endl;
            asio::write(sock, asio::buffer("test", 4));

            char reply[1024];
            size_t reply_length = asio::read(sock, asio::buffer(reply, 4));
            std::cout << "Received: ";
            std::cout.write(reply, reply_length);
            std::cout << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }
}