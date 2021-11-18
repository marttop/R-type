/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#include "BossC.hpp"
#include <iostream>

BossC::BossC(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getLocalBounds().width / 8, 0), sf::Vector2i(_sprite.getLocalBounds().width / 8, _sprite.getLocalBounds().height)));
    _sprite.setScale(sf::Vector2f(4, 4));
}

BossC::~BossC()
{
}

void BossC::update()
{
    if (!_isAlive && !_deathAnimation) {
        _deathFinish = true;
        _deathClock.restart();
    }
    if (_animationClock.getElapsedTime().asMilliseconds() > 120) {
        _animationClock.restart();
        if (_sprite.getTextureRect().left >= _sprite.getTextureRect().width * 7) {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        } else {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getTextureRect().left + _sprite.getTextureRect().width, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        }
    }
}