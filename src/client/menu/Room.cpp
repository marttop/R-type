/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Room
*/

#include "Room.hpp"

Room::Room()
{
}

Room::~Room()
{
}

void Room::create(const sf::RectangleShape &background)
{
    _ready.create(sf::Vector2f(background.getPosition().x + background.getSize().x / 4, background.getPosition().y + background.getSize().y / 2), "Ready");
    _leave.create(sf::Vector2f(background.getPosition().x - background.getSize().x / 4, background.getPosition().y + background.getSize().y / 2), "Leave");

    _background.setSize(sf::Vector2f(background.getSize().x / 1.2, background.getSize().y / 1.2));
    _background.setFillColor(sf::Color::Transparent);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(background.getPosition().x, background.getPosition().y));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _id = "";
}

void Room::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (_leave.event(event, window))
        socket.send(boost::asio::buffer("235 " + _id + "\n"));
    _ready.event(event, window);
}

void Room::update()
{
}

void Room::setId(const std::string &id)
{
    _id = id;
}

void Room::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    _leave.draw(window);
    _ready.draw(window);
}
