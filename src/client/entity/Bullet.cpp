/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture &texture, const sf::Vector2f &pos, const std::string &id)
                                                                : Entity(texture, pos, id)
{
}

Bullet::~Bullet()
{
}
