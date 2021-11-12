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
        PlayerShip(const sf::Texture &texture, const sf::Vector2f &pos, const std::string &id);
        ~PlayerShip();

    protected:
    private:
        sf::Vector2f _pos;
};

#endif /* !PLAYERSHIP_HPP_ */
