/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Heal
*/

#include "Heal.hpp"

Heal::Heal(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
}

Heal::~Heal()
{
}

void Heal::drawSprite(sf::RenderWindow &window)
{
    if (!_deathAnimation)
        window.draw(_sprite);
}

void Heal::drawParticles(sf::RenderWindow &window)
{
}