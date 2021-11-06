/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect) : ServerEntity(rect)
{
}

ServerPlayer::~ServerPlayer()
{
}

void ServerPlayer::update()
{
    std::cout << "I'm a player" << std::endl;
}