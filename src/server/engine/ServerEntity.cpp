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
                            int health,
                            int speed)
    :   _isAlive(true),  _rect(rect), _type(type), _id(id), _health(health), _speed(speed)
{
    _direction = std::make_pair(0, 0);
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

std::pair<double, double> ServerEntity::getDirection() const
{
    return (_direction);
}

std::pair<double, double> ServerEntity::getPosition() const
{
    return (_rect.getPosition());
}

double ServerEntity::getSpeed() const
{
    return (_speed);
}
