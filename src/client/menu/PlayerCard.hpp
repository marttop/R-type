/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerCard
*/

#ifndef PLAYERCARD_HPP_
#define PLAYERCARD_HPP_

#include <SFML/Graphics.hpp>

class PlayerCard {
    public:
        PlayerCard();
        ~PlayerCard();

        void create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text _name;
        sf::Font _font;
};

#endif /* !PLAYERCARD_HPP_ */
