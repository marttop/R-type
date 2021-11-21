/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Asteroids
*/

#include "Asteroids.hpp"

Asteroids::Asteroids(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setOrigin(sf::Vector2f(_sprite.getTextureRect().width / 2, _sprite.getTextureRect().height / 2));
    _rotationSpeed = rand() % 10 + 1;
    if (rand() % 2 == 0)
        _rotationSpeed *= -1;
}

Asteroids::~Asteroids()
{
}

void Asteroids::update()
{
    _particleSystem.update(sf::Vector2f{0, 50}, sf::Vector2f{_pos.x + _sprite.getTextureRect().width / 2, _pos.y}, sf::Vector2f{_pos.x , _pos.y}, sf::Color(0, 0, 255, 255), sf::Color(0, 0, 0, 255), 50, 1);

    if (_animationClock.getElapsedTime().asMilliseconds() > 50) {
        _animationClock.restart();
        _sprite.rotate(_rotationSpeed);
    }
}

void Asteroids::drawSprite(sf::RenderWindow &window)
{
    glPointSize(10);
    _particleSystem.drawParticles(window);
    window.draw(_sprite);
}

void Asteroids::drawParticles(sf::RenderWindow &window)
{
}