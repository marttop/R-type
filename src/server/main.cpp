/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include <iostream>
#include "RtypeException.hpp"
#include "AsioTcpServ.hpp"
#include "ValidateIp.hpp"
#include "ServerPlayer.hpp"

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
    constexpr bool multi_threading = true;

    std::shared_ptr<IEntity> player1 = std::make_shared<ServerPlayer>(CustomRect(10, 10));
    std::shared_ptr<IEntity> player2 = std::make_shared<ServerPlayer>(CustomRect(10, 10, 10, 10));

    std::cout << player1->isColliding(player2) << std::endl;

    srand(time(nullptr));
    try {
        asio::io_context io_context;

        AsioTcpServ server(io_context, std::atoi(av[1]));

        if constexpr (multi_threading) {
            // std::thread shell(AsioTcpServ::shell_send);
        }
        io_context.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}