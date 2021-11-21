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

        /**
         * @brief Update the PlayerShip
         * 
         * @return ** void 
         */
        void update() override;

        /**
         * @brief Draw the PlayerShip sprite
         * 
         * @param window 
         * @return ** void 
         */
        void drawSprite(sf::RenderWindow &window) override;

        /**
         * @brief Draw the PlayerShip particles
         * 
         * @param window 
         * @return ** void 
         */
        void drawParticles(sf::RenderWindow &window) override;

        /**
         * @brief Update the hp
         * 
         * @return ** void 
         */
        void updateHp();

    protected:
    private:
        sf::RectangleShape _hpRect;
        sf::RectangleShape _barRect;
};

#endif /* !PLAYERSHIP_HPP_ */
