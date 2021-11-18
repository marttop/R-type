/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor)
                    : Entity(texture, pos, speed, startColor, endColor)
{
    _sprite.setScale(sf::Vector2f(0.3, 0.3));
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::update()
{
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x - 25, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, _startColor, _endColor, 50, 1);
}

void PlayerShip::drawParticles(sf::RenderWindow &window)
{
}
void PlayerShip::drawSprite(sf::RenderWindow &window)
{
    glPointSize(7);
    _particleSystem.drawParticles(window);
    window.draw(_sprite);
}