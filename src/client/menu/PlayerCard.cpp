/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerCard
*/

#include "PlayerCard.hpp"

PlayerCard::PlayerCard()
{
}

PlayerCard::~PlayerCard()
{
}

void PlayerCard::create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name, const sf::Vector2f &factors)
{
    _background.setSize(sf::Vector2f(size.x, size.y));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));

    _font.loadFromFile("assets/fonts/OxygenMono-Regular.ttf");

    _name.setString(name);
    _name.setScale(factors);
    _name.setFont(_font);
    _name.setOrigin(sf::Vector2f(_name.getOrigin().x, _name.getGlobalBounds().height / 3));
    _name.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 1.9));

}

void PlayerCard::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
}