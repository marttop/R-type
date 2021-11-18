/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#include "BidosSlave.hpp"
#include <iostream>

BidosSlave::BidosSlave(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getLocalBounds().width / 12 * (std::rand() % 11 + 1), 0), sf::Vector2i(_sprite.getLocalBounds().width / 12, _sprite.getLocalBounds().height)));
    _sprite.setScale(sf::Vector2f(4, 4));
}

BidosSlave::~BidosSlave()
{
}

void BidosSlave::update()
{
    if (!_isAlive && !_deathAnimation) {
        _deathAnimation = true;
        _deathClock.restart();
    }
    if (_deathAnimation && _deathClock.getElapsedTime().asMilliseconds() < 1500)
        _particleSystem.update(sf::Vector2f{0, 0}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Color(255, 255, 0, 255 / (_deathClock.getElapsedTime().asMilliseconds() + 1) * 100), sf::Color(255, 0, 0, 255 / (_deathClock.getElapsedTime().asMilliseconds() + 1) * 100), 50, 1);
    else if (_deathAnimation && _deathClock.getElapsedTime().asMilliseconds() >= 1500)
        _deathFinish = true;

    if (_animationClock.getElapsedTime().asMilliseconds() > 50) {
        _animationClock.restart();
        if (_sprite.getTextureRect().left >= _sprite.getTextureRect().width * 11) {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        } else {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getTextureRect().left + _sprite.getTextureRect().width, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        }
    }
}

void BidosSlave::drawSprite(sf::RenderWindow &window)
{
    if (!_deathAnimation)
        window.draw(_sprite);
}

void BidosSlave::drawParticles(sf::RenderWindow &window)
{
    if (_deathAnimation) {
        glPointSize(5);
        _particleSystem.drawParticles(window);
    }
}