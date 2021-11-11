/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** InputBox
*/

#ifndef INPUTBOX_HPP_
#define INPUTBOX_HPP_

#include <SFML/Graphics.hpp>

#include "AssetManager.hpp"

class InputBox {
    public:
        InputBox();
        ~InputBox();

        void create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title = "", const std::string &defaultInput = "", const bool &ip = false, const bool &num = false, const bool &alpha = true, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        void event(const sf::Event &event, const sf::RenderWindow &window);
        void update();
        std::string getInputString() const;

    protected:
    private:
        sf::RectangleShape _background;
        sf::RectangleShape _cursor;
        sf::Clock _cursorClock;
        std::string _title;
        sf::Text _titleText;
        std::string _input;
        sf::Text _inputText;
        sf::Font _font;
        bool _isFocus;
        bool _ip;
        bool _num;
        bool _alpha;
};

#endif /* !INPUTBOX_HPP_ */
