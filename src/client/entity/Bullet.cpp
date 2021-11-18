/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor)
    : Entity(texture, pos, speed, startColor, endColor)
{
    _sprite.setScale(sf::Vector2f(0.6, 0.6));
    _sprite.setRotation(90);
    _moveClk.restart();
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
    if (!_isAlive && !_deathAnimation) {
        _deathAnimation = true;
        _deathClock.restart();
    }
    if (_deathAnimation && _deathClock.getElapsedTime().asMilliseconds() < 1000)
        _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Color(255, 255, 0, 255 / (_deathClock.getElapsedTime().asMilliseconds() + 1) * 100), sf::Color(255, 0, 0, 255 / (_deathClock.getElapsedTime().asMilliseconds() + 1) * 100), 20, 1);
    else if (_deathAnimation && _deathClock.getElapsedTime().asMilliseconds() >= 1000)
        _deathFinish = true;
    else
        _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x - 35, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x - 10, _pos.y + _sprite.getGlobalBounds().height / 2}, _startColor, _endColor, 15, 1);
}

void Bullet::draw(sf::RenderWindow &window)
{
    if (_deathAnimation)
        glPointSize(5);
    else
        glPointSize(3.5);
    _particleSystem.drawParticles(window);
    if (!_deathAnimation)
        window.draw(_sprite);
}