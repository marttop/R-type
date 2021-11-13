/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const std::string &id)
                    : Entity(texture, pos, id)
{
    _sprite.setScale(sf::Vector2f(0.3, 0.3));
}

PlayerShip::~PlayerShip()
{
}