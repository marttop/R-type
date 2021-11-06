/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** InputBox
*/

#ifndef INPUTBOX_HPP_
#define INPUTBOX_HPP_

#include <SFML/Graphics.hpp>

class InputBox {
    public:
        InputBox();
        ~InputBox();

        void create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title = "", const sf::Vector2f &factors = {1, 1}, const std::string &fontPath = "assets/fonts/arial.tff");
        void draw(sf::RenderWindow &window);

    protected:
    private:
        sf::RectangleShape _background;
        std::string _title;
        sf::Text _titleText;
        sf::Font _font;
};

#endif /* !INPUTBOX_HPP_ */
