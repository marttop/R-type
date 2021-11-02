/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#ifdef _WIN32
#define _WIN32_WINNT 0x00A0
#endif

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

class Server {
    public:
        Server();
        ~Server();

    protected:
    private:
};

#endif /* !SERVER_HPP_ */
