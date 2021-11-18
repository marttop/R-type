/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#include "BidosSlave.hpp"

BidosSlave::BidosSlave(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor)
    : Entity(texture, pos, speed, startColor, endColor)
{
}

BidosSlave::~BidosSlave()
{
}

void BidosSlave::update()
{
    _sprite.move(_speed, 0);
    _pos = _sprite.getPosition();
}