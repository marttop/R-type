/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "IClientEntity.hpp"
#include "Particles.hpp"

class Entity : public IClientEntity {
    public:
        Entity(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed = 0, const sf::Color &startColor = sf::Color::White, const sf::Color &endColor = sf::Color::White);
        ~Entity();

        float getElapsedTime() const;
        sf::Vector2f getPos() const;
        sf::Vector2f getSize() const;
        sf::FloatRect getGlobalBounds() const;
        void setPos(const sf::Vector2f &pos);
        void setRotation(const float &angle);
        void setColor(const sf::Color &color);

        void restartClock();
        void draw(sf::RenderWindow &window);
        void update();

    protected:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _pos;
        sf::Clock _clock;
        ParticleSystem _particleSystem;
        sf::Color _startColor;
        sf::Color _endColor;
        float _speed;

    private:
};

#endif /* !ENTITY_HPP_ */
