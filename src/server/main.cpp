/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include <iostream>
#include "AsioTcpServ.hpp"

int main(int ac, char **av)
{
    constexpr bool multi_threading = true;

    srand(time(nullptr));
    try {
        asio::io_context io_context;

        AsioTcpServ server(io_context, std::atoi(av[1]));

        if constexpr (multi_threading) {
            //TODO uncomment this line (Task 04)
            //enable_multi_threading(10, io_service);
        }
        io_context.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}