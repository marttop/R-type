/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** WarningBox
*/

#ifndef WARNINGBOX_HPP_
#define WARNINGBOX_HPP_

#include <SFML/Graphics.hpp>

#include "Button.hpp"

class WarningBox {
    public:
        WarningBox();
        ~WarningBox();

        void create(const sf::Vector2f &pos, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        void event(const sf::Event &event, const sf::RenderWindow &window);
        void open(const std::string &text);
        bool isOpen() const;

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text *_text;
        sf::Font _font;
        Button _close;
        bool _isOpen;
        sf::Vector2f _factors;
};

#endif /* !WARNINGBOX_HPP_ */
