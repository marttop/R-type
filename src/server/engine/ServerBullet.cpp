/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerBullet
*/

#include "ServerBullet.hpp"

ServerBullet::ServerBullet(const CustomRect &customRect, const std::string &type,
                        const std::string &id, int health, int speed) : ServerEntity(customRect, type, id, health, speed)
{
}

ServerBullet::~ServerBullet()
{
}

void ServerBullet::update()
{
    if (_isAlive) {
        setPosition(_rect._x + _speed, _rect._y);
        if (_rect._x >= 1850) _isAlive = false;
    }
}
