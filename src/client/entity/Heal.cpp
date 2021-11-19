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

void Heal::update()
{
    if (!_isAlive)
        _deathFinish = true;
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width / 2, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width / 2, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Color(0, 255, 0, 255), sf::Color(0, 255, 0, 0), 10, 1);
}

void Heal::drawSprite(sf::RenderWindow &window)
{
    if (!_deathAnimation) {
        _particleSystem.drawParticles(window);
        window.draw(_sprite);
    }
}

void Heal::drawParticles(sf::RenderWindow &window)
{
}