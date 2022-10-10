#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/tcp.hpp>
#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0X0A00
#endif
#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define IP_ADDRESS "localhost"

int main(int argc, char *argv[]) {

    //Error code
    asio::error_code ec;

    //Asio context, platform specific interface
    asio::io_context context;

    //Get the address of the computer we want to connect to
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(IP_ADDRESS, ec), 80);

    //Create a socket, the context will deliver the implementation
    asio::ip::tcp::socket socket(context);

    //Tell the socket to try to connect
    socket.connect(endpoint, ec);

    if(!ec)
    {
        std::cout << "Connected" << "\n";
    }
    else
    {
        std::cout << "Failed to connect to address:\n" << ec.message() << "\n";
    }

    return 0;
}
