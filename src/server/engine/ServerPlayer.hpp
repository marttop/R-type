/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ServerEntity.hpp"
#include "ServerRoom.hpp"
#include <asio.hpp>

class ServerRoom;

class ServerPlayer :  public ServerEntity, std::enable_shared_from_this<ServerPlayer> {
    public:
        ServerPlayer(const CustomRect &rect, asio::io_context &io_context, ServerRoom &roomRef, int port);
        ~ServerPlayer();

        void update() override;
        void setUsername(const std::string &username);

        std::string getUsername() const;
        int getPort() const;
        asio::ip::udp::socket &getSocket();
        void startUDP();
        bool isReady() const;
        bool setIsReady(bool isReady);
        void handleReceive(const asio::error_code &error);
        void closeUDP();

    protected:
    private:
        std::string _userName;
        asio::ip::udp::socket _socket;
        asio::io_context &_io_context;
        asio::ip::udp::endpoint _receiverEndpoint;
        ServerRoom *_roomRef;
        bool _isReady;
        char _buffer[1024];
        int _port;

};

#endif /* !PLAYER_HPP_ */
