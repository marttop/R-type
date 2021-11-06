/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerEntity
*/

#include "ServerEntity.hpp"

ServerEntity::ServerEntity()
{
    _rect = new CustomRect(10, 10);
}

ServerEntity::~ServerEntity()
{
    delete _rect;
}

void ServerEntity::sendData()
{
}

bool ServerEntity::isAlive() const
{
    return true;
}

CustomRect ServerEntity::getRect() const
{
    return (*_rect);
}

bool ServerEntity::isColliding(const std::shared_ptr<IEntity> &other) const
{
    return (_rect->isColliding(other->getRect()));
}