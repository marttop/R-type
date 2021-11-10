/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** WarningBox
*/

#include "WarningBox.hpp"

WarningBox::WarningBox()
{
    _text = nullptr;
}

WarningBox::~WarningBox()
{
    if (_text)
        delete _text;
}

void WarningBox::create(const sf::Vector2f &pos, const sf::Vector2f &factors)
{
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));

    _isOpen = false;

    _font.loadFromFile("assets/fonts/OxygenMono-Regular.ttf");

    _text = new sf::Text;
    _text->setString("");
    _factors = factors;
}

void WarningBox::open(const std::string &text, const bool &isButton)
{
    if (text != _text->getString() || _text->getString() == "") {
        delete _text;
        _text = new sf::Text;
        _text->setString(text);
        _text->setFont(_font);
        _text->setScale(_factors);
        _text->setOrigin(sf::Vector2f(_text->getGlobalBounds().left + _text->getGlobalBounds().width / 2, _text->getGlobalBounds().top + _text->getGlobalBounds().height / 1.5));
        _text->setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));

        _background.setSize(sf::Vector2f(_text->getGlobalBounds().width * 1.5, _text->getGlobalBounds().height * 5));
        _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

        _isButton = isButton;

        if (_isButton)
            _close.create(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 2 - _background.getSize().x / 4, _background.getPosition().y + _background.getSize().y / 2), "Close", sf::Vector2f(1, 1));
    }
    _isOpen = true;
}

bool WarningBox::isOpen() const
{
    return (_isOpen);
}

void WarningBox::draw(sf::RenderWindow &window) const
{
    if (_isOpen == true) {
        window.draw(_background);
        window.draw(*_text);
        if (_isButton)
            _close.draw(window);
    }
}

void WarningBox::event(const sf::Event &event, const sf::RenderWindow &window)
{
    if (_isButton && _close.event(event, window))
        _isOpen = false;
}