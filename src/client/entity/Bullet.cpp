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
    // if (_moveClk.getElapsedTime().asMilliseconds() >= 22) {
        _sprite.move(sf::Vector2f(_speed, 0));
        _pos = _sprite.getPosition();
        _moveClk.restart();
    // }
    _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x - 25, _pos.y + _sprite.getGlobalBounds().height / 2}, _startColor, sf::Color::Black, 15, 1);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    glPointSize(3.5);
    _particleSystem.drawParticles(window);
}