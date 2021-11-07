/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::create(const sf::RenderWindow &window)
{
    _background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 1.5));
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(4.0);
    _background.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _nameBox.create(sf::Vector2f(_background.getSize().x / 3, _background.getSize().y / 16), sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 3), "Choose your name", sf::Vector2f(1, 1), false);
}

void Menu::update(const sf::Event &event, const sf::RenderWindow &window)
{
    _nameBox.update(event, window);
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_background);
    _nameBox.draw(window);
}