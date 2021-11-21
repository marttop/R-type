/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Asteroids
*/

#ifndef ASTEROIDS_HPP_
#define ASTEROIDS_HPP_

#include "Entity.hpp"

class Asteroids : public Entity {
    public:
        Asteroids(const sf::Texture &texture,
                    const sf::Vector2f &pos,
                    const float &speed,
                    const sf::Color &startColor,
                    const sf::Color &endColor,
                    int health);
        ~Asteroids();

        void update() override;
        void drawParticles(sf::RenderWindow &window) override;
        void drawSprite(sf::RenderWindow &window) override;

    protected:
    private:
        int _rotationSpeed;
};

#endif /* !ASTEROIDS_HPP_ */
