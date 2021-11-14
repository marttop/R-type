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
        PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const sf::Color &startColor, const sf::Color &endColor);
        ~PlayerShip();

        void update();

    protected:
    private:
};

#endif /* !PLAYERSHIP_HPP_ */
