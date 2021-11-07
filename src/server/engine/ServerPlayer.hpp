/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ServerEntity.hpp"
#include <asio.hpp>

class ServerPlayer : public ServerEntity {
    public:
        ServerPlayer(const CustomRect &rect, asio::io_context &io_context);
        ~ServerPlayer();

        void update() override;
        void setUsername(const std::string &username);

        std::string getUsername() const;
        asio::ip::tcp::socket &getSocket();

    protected:
    private:
        std::string _userName;
        asio::ip::udp::socket _socket;
        asio::io_context &_io_context;

};

#endif /* !PLAYER_HPP_ */
