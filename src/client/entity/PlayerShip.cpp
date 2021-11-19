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
    _hpRect.setSize(sf::Vector2f{102, 6});
    _barRect.setSize(sf::Vector2f{106, 10});
    _barRect.setOutlineThickness(2.0);
    _hpRect.setFillColor(sf::Color::Green);
    _barRect.setOutlineColor(sf::Color::White);
    _barRect.setFillColor(sf::Color::Transparent);
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::updateHp()
{
    float x = 0;

    x = (_health * 102) / _maxHealth;

    if (x < 0)
        _hpRect.setSize(sf::Vector2f{0, 6});
    else
        _hpRect.setSize(sf::Vector2f{x, 6});
    float y = 0;

    y = (_health * 100) / _maxHealth;

    if (y > 66)
        _hpRect.setFillColor(sf::Color::Green);
    else if (y > 33 && y <= 66)
        _hpRect.setFillColor(sf::Color::Yellow);
    if (y > 0 && y <= 33)
        _hpRect.setFillColor(sf::Color::Red);
}

void PlayerShip::update()
{
    if (_isAlive) {
        _barRect.setPosition(sf::Vector2f(_pos.x + 55, _pos.y - 20));
        _hpRect.setPosition(sf::Vector2f(_pos.x + 2 + 55, _pos.y + 2 - 20));
        updateHp();
        _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x - 25, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / static_cast<float>(1.75)}, _startColor, _endColor, 50, 1);
    }
}

void PlayerShip::drawParticles(sf::RenderWindow &window)
{
}

void PlayerShip::drawSprite(sf::RenderWindow &window)
{
    if (_isAlive) {
        glPointSize(7);
        _particleSystem.drawParticles(window);
        window.draw(_sprite);
        window.draw(_barRect);
        window.draw(_hpRect);
    }
}