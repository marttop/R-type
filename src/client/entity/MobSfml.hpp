/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MobSfml
*/

#ifndef MOBSFML_HPP_
#define MOBSFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "IEntity.hpp"

class MobSfml {
public:
        MobSfml(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed = 0, const sf::Color &startColor = sf::Color::White, const sf::Color &endColor = sf::Color::White);
        ~MobSfml();

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
        sf::Color _startColor;
        sf::Color _endColor;
        float _speed;

    private:
};

#endif /* !MOBSFML_HPP_ */