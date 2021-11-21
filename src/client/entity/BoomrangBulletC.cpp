/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#include "BoomrangBulletC.hpp"
#include <iostream>

BoomrangBulletC::BoomrangBulletC(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getLocalBounds().width / 12 * (std::rand() % 11 + 1), 0), sf::Vector2i(_sprite.getLocalBounds().width / 12, _sprite.getLocalBounds().height)));
    _sprite.setScale(sf::Vector2f(4, 4));
}

BoomrangBulletC::~BoomrangBulletC()
{
}

void BoomrangBulletC::update()
{
    if (!_isAlive)
        _deathFinish = true;

    _particleSystem.update(sf::Vector2f{25, 25}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width / 2, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width / 2, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Color(0, 255, 255, 200), sf::Color(255, 255, 255, 50), 20, 1);

    if (_animationClock.getElapsedTime().asMilliseconds() > 50) {
        _animationClock.restart();
        if (_sprite.getTextureRect().left >= _sprite.getTextureRect().width * 11) {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        } else {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getTextureRect().left + _sprite.getTextureRect().width, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        }
    }
}

void BoomrangBulletC::drawSprite(sf::RenderWindow &window)
{
    glPointSize(5);
    _particleSystem.drawParticles(window);
    window.draw(_sprite);
}

void BoomrangBulletC::drawParticles(sf::RenderWindow &window)
{
}