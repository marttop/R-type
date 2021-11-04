/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        std::cout << argv[1] << std::endl;
        auto endpoints = tcp::endpoint( boost::asio::ip::address::from_string(argv[1]), 4242);
        tcp::socket socket(io_context);

        socket.connect( endpoints);
        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            std::cout.write(buf.data(), len);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::string test = "";

            std::cin >> test;

            test += "/r/n";

            socket.write_some(boost::asio::buffer(test), error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}