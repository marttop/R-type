/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Heal
*/

#ifndef HEAL_HPP_
#define HEAL_HPP_

#include "Entity.hpp"

class Heal : public Entity {
    public:
        Heal(const sf::Texture &texture, const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor, int health);
        ~Heal();

        /**
         * @brief Draw the Heal sprite
         * 
         * @param window 
         * @return ** void 
         */
        void drawSprite(sf::RenderWindow &window) override;

        /**
         * @brief Draw the Heal particles
         * 
         * @param window 
         * @return ** void 
         */
        void drawParticles(sf::RenderWindow &window) override;

        /**
         * @brief Update the Heal
         * 
         * @return ** void 
         */
        void update() override;

    protected:
    private:
};

#endif /* !HEAL_HPP_ */
