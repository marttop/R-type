/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** IClientEntity
*/

#ifndef ICLIENTENTITY_HPP_
#define ICLIENTENTITY_HPP_

#include <SFML/Graphics.hpp>

class IClientEntity {
    public:
        IClientEntity() = default;
        virtual ~IClientEntity() = default;

        virtual float getElapsedTime() const = 0;
        virtual sf::Vector2f getPos() const = 0;
        virtual sf::Vector2f getSize() const = 0;
        virtual sf::FloatRect getGlobalBounds() const = 0;
        virtual void setPos(const sf::Vector2f &pos) = 0;
        virtual void setRotation(const float &angle) = 0;
        virtual void setColor(const sf::Color &color) = 0;
        virtual void setHealth(int health) = 0;

        virtual void restartClock() = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual void update() = 0;
        virtual bool isAlive() const = 0;
        virtual void setIsAlive(bool isAlive) = 0;

    protected:
    private:
};

#endif /* !ICLIENTENTITY_HPP_ */
