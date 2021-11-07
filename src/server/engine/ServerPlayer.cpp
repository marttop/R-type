/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect, asio::io_context &io_context)
                            : ServerEntity(rect), _io_context(io_context), _socket(io_context)
{
    _userName = "";
}

ServerPlayer::~ServerPlayer()
{
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