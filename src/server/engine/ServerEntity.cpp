/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerEntity
*/

#include "ServerEntity.hpp"

ServerEntity::ServerEntity(const CustomRect &rect,
                            const std::string &type,
                            int id,
                            int health)
    :   _isAlive(true),  _rect(rect), _type(type), _id(id), _health(health)
{
}

ServerEntity::~ServerEntity()
{
}

void ServerEntity::sendData()
{
}

bool ServerEntity::isAlive() const
{
    return true;
}

void ServerEntity::addLifeEntity(int lifeAdded)
{
    _health += lifeAdded;
}

int ServerEntity::getId() const
{
    return (_id);
}

void ServerEntity::setId(int id)
{
    _id = id;
}

CustomRect ServerEntity::getRect() const
{
    return (_rect);
}

bool ServerEntity::isColliding(const std::shared_ptr<IEntity> &other) const
{
    return (_rect.isColliding(other->getRect()));
}