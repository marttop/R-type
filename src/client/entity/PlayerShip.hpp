/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#ifndef PLAYERSHIP_HPP_
#define PLAYERSHIP_HPP_

#include "Entity.hpp"

class PlayerShip : public Entity {
    public:
        PlayerShip(const sf::Texture &texture,
                    const sf::Vector2f &pos,
                    const float &speed,
                    const sf::Color &startColor,
                    const sf::Color &endColor,
                    int health);
        ~PlayerShip();

        void update() override;
        void drawSprite(sf::RenderWindow &window) override;
        void drawParticles(sf::RenderWindow &window) override;
        void updateHp(int hp) override;

    protected:
    private:
        sf::RectangleShape _hpRect;
        sf::RectangleShape _barRect;
};

#endif /* !PLAYERSHIP_HPP_ */
