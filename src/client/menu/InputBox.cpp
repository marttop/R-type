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

void InputBox::create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title, const sf::Vector2f &factors, const std::string &fontPath)
{
    _background.setSize(sf::Vector2f(size.x, size.y));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _titleText.setString(_title);
    _titleText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));
    _titleText.setScale(factors);
    _font.loadFromFile(fontPath);
    _titleText.setFont(_font);
}

void InputBox::draw(sf::RenderWindow &window)
{
    window.draw(_background);
    if (_titleText.getString() != "")
        window.draw(_titleText);
}