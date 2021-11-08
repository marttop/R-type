/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sys/types.h>
#include <unistd.h>
#include "RtypeException.hpp"
#include "ValidateIp.hpp"

using boost::asio::ip::udp;

int arg_check(int ac, char *argv[])
{
    if (ac < 3) throw rtype::RtypeException("./rtype_server ip port");
    if (std::atoi(argv[2]) < 1025 || std::atoi(argv[2]) > 65535)
        throw rtype::RtypeException("Please provide a valid port (1025 to 65535).");
    ValidateIp validator;
    if (validator.validateIpAddress(argv[1]) == 0)
        throw rtype::RtypeException("Please provide a valid ip address.");
    return (0);
}


int main(int ac, char* av[])
{
    try
    {
        arg_check(ac, av);

        boost::asio::io_context io_context;
        udp::resolver resolver(io_context);
        std::cout << av[1] << std::endl;
        auto endpoints = udp::endpoint( boost::asio::ip::address::from_string(av[1]), 8888);
        udp::socket socket(io_context);
            boost::array<char, 128> buf;
            boost::system::error_code error;
        pid_t eric;

        socket.connect( endpoints);
            eric = fork();
        for (;;)
        {



            if (eric == 0) {

                size_t len = socket.receive_from(boost::asio::buffer(buf), endpoints);
                std::cout.write(buf.data(), len);
            }
            else {

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::string test = "";

                std::cout << "msg: ";
                std::cin >> test;

                test += "\n";

                socket.send_to(boost::asio::buffer(test), endpoints);

            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}