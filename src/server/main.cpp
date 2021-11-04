/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include "tcp_server.hpp"

int main(int ac, char **av)
{
    constexpr bool multi_threading = true;

    srand(time(nullptr));
    try {
        boost::asio::io_service io_service;

        tcp_server server(io_service);
        if constexpr (multi_threading) {
            //TODO uncomment this line (Task 04)
            //enable_multi_threading(10, io_service);
        }
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}