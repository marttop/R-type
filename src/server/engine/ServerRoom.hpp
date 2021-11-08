/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerRoom
*/

#ifndef SERVERROOM_HPP_
#define SERVERROOM_HPP_

#include "UserConnection.hpp"
#include "ServerPlayer.hpp"

class ServerRoom {
    public:
        ServerRoom(asio::io_context& io_context);
        ~ServerRoom();
        void addUser(int id, const std::string &username);
        int getNbUsers() const;

    protected:
    private:
        std::vector<std::shared_ptr<ServerPlayer>> _playerList;
        asio::io_context &_io_context;
};

#endif /* !SERVERROOM_HPP_ */
