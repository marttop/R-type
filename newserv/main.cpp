/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "RtypeException.hpp"
#include "ValidateIp.hpp"

int arg_check(int ac, char *argv[])
{
    ValidateIp validator;
    if (ac < 2)
        throw rtype::RtypeException("./rtype_server port");
    if (std::atoi(argv[1]) < 1 || std::atoi(argv[1]) > 65535)
        throw rtype::RtypeException("Please provide a valid port (1025 to 65535).");
    return (0);
}

int main(int ac, char **av)
{
    try {
        arg_check(ac, av);
        asio::error_code ec;
        asio::io_context context;
        asio::ip::tcp::socket socket(context);
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), std::atoi(av[1]));

        socket.connect(endpoint, ec);

        if (!ec) {
            std::cout << "Server on!" << std::endl;
        } else {
            std::cout << "failed to connect to address:\n" << ec.message() << std::endl;
        }
    }
    catch (const rtype::RtypeException &e) {
        std::cerr << WHERE << std::endl << "\t" << e.what() << std::endl;
        return (84);
    }

    return 0;
}