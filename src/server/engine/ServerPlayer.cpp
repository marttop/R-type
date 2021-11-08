/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect, asio::io_context &io_context)
                            : ServerEntity(rect), _io_context(io_context),
                            _socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8888))
{
    _userName = "";
    std::memset(_buffer, '\0', 1024);
}

ServerPlayer::~ServerPlayer()
{
}

void ServerPlayer::startUDP()
{
    _socket.async_receive(asio::buffer(_buffer),
                            std::bind(&ServerPlayer::handleReceive, this,
                                    std::placeholders::_1));
}

void ServerPlayer::handleReceive(const asio::error_code &error)
{
    std::cout << "udp line: " << _buffer;

    _socket.async_receive(asio::buffer(_buffer),
                            std::bind(&ServerPlayer::handleReceive, this,
                                    std::placeholders::_1));
}

asio::ip::udp::socket &ServerPlayer::getSocket()
{
    return (_socket);
}

void ServerPlayer::update()
{
    std::cout << "I'm a player" << std::endl;
}

void ServerPlayer::setUsername(const std::string &username)
{
    _userName = username;
}

std::string ServerPlayer::getUsername() const
{
    return (_userName);
}