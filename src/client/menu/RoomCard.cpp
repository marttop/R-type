/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomCard
*/

#include "RoomCard.hpp"

RoomCard::RoomCard()
{
}

RoomCard::~RoomCard()
{
}

void RoomCard::create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text, const int &users, const double &thickness, const sf::Vector2f &factors)
{
    _outline = sf::Color::White;

    _thickness = thickness;

    _background.setSize(sf::Vector2f(size.x - _thickness * 4, size.y - _thickness * 2));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(_outline);
    _background.setOutlineThickness(_thickness);
    _background.setPosition(sf::Vector2f(pos.x, pos.y + _thickness * 2));

    _font.loadFromFile("assets/fonts/OxygenMono-Regular.ttf");

    _title.setString(text);
    _title.setScale(factors);
    _title.setFont(_font);
    _title.setOrigin(sf::Vector2f(_title.getOrigin().x, _title.getGlobalBounds().top + _title.getGlobalBounds().height / 2));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 2));
}

void RoomCard::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(_title);
}

sf::Vector2f RoomCard::getPosition() const
{
    return (_background.getPosition());
}

void RoomCard::incrementPosition()
{
    _background.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y + _background.getSize().y + _thickness * 2));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 2));
}

void RoomCard::decrementPosition()
{
    _background.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y - _thickness * 2));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 2));
}

sf::Vector2f RoomCard::getSize() const
{
    return (_background.getSize());
}

bool RoomCard::event(const sf::Event &event, const sf::RenderWindow &window)
{
    bool clicked = false;
    if (event.type == sf::Event::MouseMoved) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _outline = sf::Color::Yellow;
            _background.setOutlineColor(_outline);
        }
        else {
            _outline = sf::Color::White;
            _background.setOutlineColor(_outline);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _background.setFillColor(sf::Color::White);
            //_text->setFillColor(sf::Color::Black);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        _background.setFillColor(sf::Color::Black);
        //_text->setFillColor(sf::Color::White);
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            clicked = true;
            _background.setOutlineColor(sf::Color::White);
        }
    }
    return (clicked);
}