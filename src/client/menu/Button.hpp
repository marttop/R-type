/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>

class Button {
    public:
        Button();
        ~Button();

        void create(const sf::Vector2f &pos, const std::string &text, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        bool event(const sf::Event &event, const sf::RenderWindow &window);

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text *_text;
        sf::Font _font;
};

#endif /* !BUTTON_HPP_ */
