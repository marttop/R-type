/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Heal
*/

#include "Heal.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new Heal;
}
#endif

Heal::Heal()
    : ServerEntity(CustomRect(35, 35))
{
    _speed = -3;
    _type = "Heal";
    _health = -1;
    _maxHealth = _health;

    _isPickable = true;
}

Heal::~Heal()
{
}

void Heal::update()
{
    if (getPosition().first < -200) {
        _isAlive = false;
    }
    setPosition(getPosition().first + _speed, getPosition().second);
}
