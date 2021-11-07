/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** InputBox
*/

#include "InputBox.hpp"

InputBox::InputBox()
{
}

InputBox::~InputBox()
{
}

void InputBox::create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title, const sf::Vector2f &factors, const bool &dot)
{
    _background.setSize(sf::Vector2f(size.x, size.y));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _font.loadFromFile("assets/fonts/OxygenMono-Regular.ttf");

    _title = title;

    _titleText.setString(_title);
    _titleText.setScale(factors);
    _titleText.setFont(_font);
    _titleText.setOrigin(sf::Vector2f(_titleText.getGlobalBounds().width / 2, _titleText.getGlobalBounds().height / 2));
    _titleText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 2 - _titleText.getGlobalBounds().height));

    _cursor.setSize(sf::Vector2f(2.0, size.y / 1.4));
    _cursor.setFillColor(sf::Color::White);
    _cursor.setOrigin(sf::Vector2f(_cursor.getSize().x / 2, _cursor.getSize().y / 2));
    _cursor.setPosition(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2 + 10, _background.getPosition().y));

    _cursorClock.restart();

    _input = "";

    _inputText.setString(_input);
    _inputText.setFont(_font);
    _inputText.setOrigin(sf::Vector2f(0, _inputText.getGlobalBounds().height / 2 + 5));
    _inputText.setPosition(sf::Vector2f(_cursor.getPosition().x, _cursor.getPosition().y - _cursor.getSize().y / 2));

    _isFocus = false;

    _dot = dot;
}

void InputBox::update(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        printf("ass\n");
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _isFocus = true;
            _background.setOutlineColor(sf::Color::Yellow);
        }
        else {
            _isFocus = false;
            _background.setOutlineColor(sf::Color::White);
        }
    }
    if (event.type == sf::Event::TextEntered && _isFocus == true) {
        if ((event.text.unicode >= 'a' && event.text.unicode <= 'z')
        || (event.text.unicode >= 'A' && event.text.unicode <= 'Z')
        || (event.text.unicode >= '0' && event.text.unicode <= '9')
        || (event.text.unicode == '.' && _dot == true)) {
            if (_input.size() > 15)
            return;
            _input += event.text.unicode;
        }
        if (event.text.unicode == 8 && _input.size() > 0)
            _input.pop_back();
        _inputText.setString(_input);
        _cursor.setPosition(sf::Vector2f(_inputText.getGlobalBounds().left + _inputText.getGlobalBounds().width + 4, _cursor.getPosition().y));
    }
}

void InputBox::draw(sf::RenderWindow &window)
{
    window.draw(_background);
    if (_isFocus == true) {
        if (_cursorClock.getElapsedTime().asSeconds() >= 0.8)
            _cursorClock.restart();
        else if (_cursorClock.getElapsedTime().asSeconds() >= 0.4)
            window.draw(_cursor);
    }
    if (_titleText.getString() != "")
        window.draw(_titleText);
    if (_inputText.getString() != "")
        window.draw(_inputText);
}