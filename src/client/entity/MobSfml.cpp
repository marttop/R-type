/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MobSfml
*/

#include "MobSfml.hpp"

MobSfml::MobSfml(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor)
{
    _texture = texture;
    _pos = pos;
    _sprite.setTexture(_texture);
    _sprite.setPosition(_pos);
    _clock.restart();
    _startColor = startColor;
    _endColor = endColor;
    _speed = speed;
}

MobSfml::~MobSfml()
{
}

sf::FloatRect MobSfml::getGlobalBounds() const
{
    return (_sprite.getGlobalBounds());
}

float MobSfml::getElapsedTime() const
{
    return (_clock.getElapsedTime().asSeconds());
}

void MobSfml::restartClock()
{
    _clock.restart();
}

sf::Vector2f MobSfml::getPos() const
{
    return (_pos);
}

sf::Vector2f MobSfml::getSize() const
{
    return (sf::Vector2f{getGlobalBounds().width, getGlobalBounds().height});
}

void MobSfml::setPos(const sf::Vector2f &pos)
{
    _pos = pos;
    _sprite.setPosition(_pos);
}

void MobSfml::setColor(const sf::Color &color)
{
    _sprite.setColor(color);
}

void MobSfml::setRotation(const float &angle)
{
    _sprite.rotate(angle);
}

void MobSfml::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    glPointSize(7);
}

void MobSfml::update()
{
}