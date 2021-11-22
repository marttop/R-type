/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Asteroids
*/

#include "Asteroids.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new Asteroids;
}
#endif

Asteroids::Asteroids()
    : ServerEntity(CustomRect(200, 200))
{
    int x = std::rand() % 200 + 2000;
    int y = std::rand() % 800;
    setPosition(x, y);
    _speed = -(rand() % 5 + 5);
    _health = 1;
    _maxHealth = _health;
    _type = "Asteroids";

    _isObstacle = true;
    _isMobHarmful = true;
}

Asteroids::~Asteroids()
{
}

void Asteroids::update()
{
    if (getPosition().first < -500)
        _isAlive = false;
    setPosition(getPosition().first + _speed, getPosition().second);
}