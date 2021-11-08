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
        ServerRoom(asio::io_context& io_context, int id);
        ~ServerRoom();
        void addUser(int id, const std::string &username);
        int getNbUsers() const;
        std::string getPlayersName() const;
        int getId() const;

    protected:
    private:
        std::vector<std::shared_ptr<ServerPlayer>> _playerList;
        asio::io_context &_io_context;
        asio::ip::udp::endpoint remote_endpoint_;
        int _id;
};

#endif /* !SERVERROOM_HPP_ */
