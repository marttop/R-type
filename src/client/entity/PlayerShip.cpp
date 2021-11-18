/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
                    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setScale(sf::Vector2f(0.3, 0.3));
    _hpRect.setSize(sf::Vector2f{276, 16});
    _hpRect.setFillColor(sf::Color::Green);
    _barRect.setSize(sf::Vector2f{280, 20});
    _barRect.setOutlineThickness(2.0);
    _barRect.setOutlineColor(sf::Color::White);
    _barRect.setFillColor(sf::Color::Transparent);
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::updateHp(int hp)
{
    int x = 0;

    x = (hp * 276) / _health;

    if (x < 0)
        _hpRect.setSize(sf::Vector2f{0, 16});
    else
        _hpRect.setSize(sf::Vector2f{x, 16});
    int y = 0;

    y = (hp * 100) / _health;

    if (y > 66)
        _hpRect.setFillColor(sf::Color::Green);
    else if (y > 33 && y <= 66)
        _hpRect.setFillColor(sf::Color::Yellow);
    if (y > 0 && y <= 33)
        _hpRect.setFillColor(sf::Color::Red);
}

void PlayerShip::update()
{
    _hpRect.setPosition(_pos);
    _barRect.setPosition(_pos);
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x - 25, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, _startColor, _endColor, 50, 1);
}