/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Button
*/

#include "Button.hpp"

Button::Button()
{
    _text = nullptr;
}

Button::~Button()
{
    if (_text)
        delete _text;
}

void Button::create(const sf::Vector2f &pos, const std::string &text, const sf::Vector2f &factors)
{
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));

    _font.loadFromFile("assets/fonts/OxygenMono-Regular.ttf");

    _text = new sf::Text;
    _text->setString(text);
    _text->setScale(factors);
    _text->setFont(_font);
    _text->setOrigin(sf::Vector2f(_text->getGlobalBounds().left + _text->getGlobalBounds().width / 2, _text->getGlobalBounds().top + _text->getGlobalBounds().height / 2));
    _text->setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));

    _background.setSize(sf::Vector2f(_text->getGlobalBounds().width * 2, _text->getGlobalBounds().height * 2));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));
}

void Button::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(*_text);
}

bool Button::event(const sf::Event &event, const sf::RenderWindow &window)
{
    bool clicked = false;
    if (event.type == sf::Event::MouseMoved) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _background.setOutlineColor(sf::Color::Yellow);
        }
        else {
            _background.setOutlineColor(sf::Color::White);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _background.setFillColor(sf::Color::White);
            _text->setFillColor(sf::Color::Black);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        _background.setFillColor(sf::Color::Black);
        _text->setFillColor(sf::Color::White);
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            clicked = true;
            _background.setOutlineColor(sf::Color::White);
        }
    }
    return (clicked);
}