/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>

class Menu {
    public:
        Menu();
        ~Menu();

        void draw(sf::RenderWindow &window);
        void create(const sf::RenderWindow &window);

    protected:
    private:
        sf::RectangleShape _background;
};

#endif /* !MENU_HPP_ */
