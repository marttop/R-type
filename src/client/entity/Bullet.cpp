/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture &texture, const sf::Vector2f &pos, const sf::Color &startColor, const sf::Color &endColor)
    : Entity(texture, pos, startColor, endColor)
{
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x, _pos.y}, sf::Vector2f{_pos.x, _pos.y}, _startColor, _endColor, 30, 1);
}