/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Layer
*/

#include "Layer.hpp"

Layer::Layer(const sf::Texture &texture, const sf::Vector2f &pos, const bool &active) : Entity(texture, pos)
{
    _isActive = active;
}

Layer::~Layer()
{
}

void Layer::setActive(const bool &activation)
{
    _isActive = activation;
}

bool Layer::isActive() const
{
    return (_isActive);
}