/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const sf::Color &startColor, const sf::Color &endColor)
                    : Entity(texture, pos, startColor, endColor)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::update()
{
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x - 25, _pos.y}, sf::Vector2f{_pos.x, _pos.y}, _startColor, _endColor, 30, 1);
}