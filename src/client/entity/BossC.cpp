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
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_sprite.getLocalBounds().width / 8, _sprite.getLocalBounds().height)));
    _sprite.setScale(sf::Vector2f(4, 4));
    _hpRect.setSize(sf::Vector2f{390, 20});
    _barRect.setSize(sf::Vector2f{394, 22});
    _barRect.setOutlineThickness(2.0);
    _hpRect.setFillColor(sf::Color::Green);
    _barRect.setOutlineColor(sf::Color::White);
    _barRect.setFillColor(sf::Color::Transparent);
    _barRect.setPosition(sf::Vector2f(800, 15));
    _hpRect.setPosition(sf::Vector2f(801, 16));
    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");
    _name.setString("BOSS");
    _name.setFont(_font);
    _name.setPosition(sf::Vector2f(800 + 195 - _name.getGlobalBounds().width / 2, 42));
}

BossC::~BossC()
{
}

void BossC::updateHp()
{
    float x = 0;

    x = (_health * 390) / _maxHealth;

    if (x < 0)
        _hpRect.setSize(sf::Vector2f{0, 20});
    else
        _hpRect.setSize(sf::Vector2f{x, 20});
    float y = 0;

    y = (_health * 100) / _maxHealth;

    if (y > 66)
        _hpRect.setFillColor(sf::Color::Green);
    else if (y > 33 && y <= 66)
        _hpRect.setFillColor(sf::Color::Yellow);
    if (y > 0 && y <= 33)
        _hpRect.setFillColor(sf::Color::Red);
}

void BossC::drawSprite(sf::RenderWindow &window)
{
    window.draw(_name);
    window.draw(_barRect);
    window.draw(_hpRect);
    window.draw(_sprite);
}

void BossC::update()
{
    updateHp();
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