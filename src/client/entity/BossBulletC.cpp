/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#include "BossBulletC.hpp"

BossBulletC::BossBulletC(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health)
    : Entity(texture, pos, speed, startColor, endColor, health)
{
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getLocalBounds().width / 3 * (std::rand() % 2 + 1), 0), sf::Vector2i(_sprite.getLocalBounds().width / 3, _sprite.getLocalBounds().height)));
    _sprite.setScale(sf::Vector2f(4, 4));

    _shootBuf = AssetManager<sf::SoundBuffer>::getAssetManager().getAsset("assets/sounds/boss_shoot.ogg");
    _shoot.setBuffer(_shootBuf);
    _shoot.setVolume(20);
    _shoot.play();
}

BossBulletC::~BossBulletC()
{
}

void BossBulletC::update()
{
    if (!_isAlive)
        _deathFinish = true;

    _particleSystem.update(sf::Vector2f{0, 10}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Vector2f{_pos.x + _sprite.getGlobalBounds().width / 2, _pos.y + _sprite.getGlobalBounds().height / 2}, sf::Color(0, 255, 255, 200), sf::Color(255, 255, 255, 50), 20, 1);

    if (_animationClock.getElapsedTime().asMilliseconds() > 50) {
        _animationClock.restart();
        if (_sprite.getTextureRect().left >= _sprite.getTextureRect().width * 2) {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        } else {
            _sprite.setTextureRect(sf::IntRect(sf::Vector2i(_sprite.getTextureRect().left + _sprite.getTextureRect().width, 0), sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height)));
        }
    }
}

void BossBulletC::drawSprite(sf::RenderWindow &window)
{
    glPointSize(5);
    _particleSystem.drawParticles(window);
    window.draw(_sprite);
}

void BossBulletC::drawParticles(sf::RenderWindow &window)
{
}