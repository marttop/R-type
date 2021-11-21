/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.hpp"

class Button {
    public:
        Button();
        ~Button();

        void create(const sf::Vector2f &pos, const std::string &text, const sf::Vector2f &offset = {0, 0}, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        bool event(const sf::Event &event, const sf::RenderWindow &window);
        bool isMouseHovering(const sf::RenderWindow &window) const;
        void setPosition(const sf::Vector2f &pos);
        bool update(const sf::RenderWindow &window, const bool &isDrawn);

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text *_text;
        sf::Font _font;
        sf::Color _outline;
        sf::Vector2f _offset;
        sf::Sound _click;
        sf::SoundBuffer _clickBuf;
        sf::Sound _hover;
        sf::SoundBuffer _hoverBuf;
};

#endif /* !BUTTON_HPP_ */
