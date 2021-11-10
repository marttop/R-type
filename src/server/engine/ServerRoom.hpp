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

class ServerPlayer;

class ServerRoom {
    public:
        ServerRoom(asio::io_context& io_context, int id, int portSeed);
        ~ServerRoom();
        void addUser(int id, const std::string &username);
        void removeUser(int id);
        int getNbUsers() const;
        std::string getPlayersName() const;
        bool isPlayerInRoom(int id) const;
        std::shared_ptr<ServerPlayer> getPlayerFromId(int id) const;
        int getId() const;

    protected:
    private:
        std::vector<std::shared_ptr<ServerPlayer>> _playerList;
        asio::io_context &_io_context;
        asio::ip::udp::endpoint remote_endpoint_;
        void startGame();
        int _id;
        int _portSeed;
};

#endif /* !SERVERROOM_HPP_ */
