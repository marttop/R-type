/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerEntity
*/

#include "ServerEntity.hpp"

ServerEntity::ServerEntity(const CustomRect &rect,
                            const std::string &type,
                            const std::string &id,
                            int speed,
                            int health)
    :   _isAlive(true),  _rect(rect), _type(type), _id(id), _speed(speed), _health(health)
{
    _direction = std::make_pair(0, 0);
    _maxHealth = health;
}

ServerEntity::~ServerEntity()
{
}

int ServerEntity::getMaxHp() const
{
    return (_maxHealth);
}

void ServerEntity::sendData()
{
}

int ServerEntity::getHp() const
{
    return (_health);
}

bool ServerEntity::isAlive() const
{
    return (_isAlive);
}

void ServerEntity::setAlive(bool life)
{
    _isAlive = life;
}

void ServerEntity::addLifeEntity(int lifeAdded)
{
    if (lifeAdded + _health > _maxHealth) {
        _health = _maxHealth;
        return;
    }
    if (_health > 0) {
        _health += lifeAdded;
    } else {
        _isAlive = false;
    }
}

std::string ServerEntity::getId() const
{
    return (_id);
}

void ServerEntity::setId(const std::string id)
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

void ServerEntity::setDirection(double x, double y)
{
    _direction.first = x;
    _direction.second = y;
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

void ServerEntity::setPosition(double x, double y)
{
    _rect.setPosition(x, y);
}

std::string ServerEntity::getType() const
{
    return (_type);
}

std::vector<std::shared_ptr<IEntity>> ServerEntity::getAmmos() const
{
    return (_ammos);
}

void ServerEntity::clearAmmos()
{
    _ammos.clear();
}