/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomsList
*/

#include "RoomsList.hpp"

RoomsList::RoomsList()
{
}

RoomsList::~RoomsList()
{
}

void RoomsList::create(const sf::RectangleShape &background)
{
    _join.create(sf::Vector2f(background.getPosition().x + background.getPosition().x / 2.3, background.getPosition().y + background.getSize().y / 2), "Join");
    _create.create(sf::Vector2f(background.getPosition().x + background.getPosition().x / 4, background.getPosition().y + background.getSize().y / 2), "Create");
    _disconnect.create(sf::Vector2f(background.getPosition().x - background.getPosition().x / 3, background.getPosition().y + background.getSize().y / 2), "Disconnect");
}

void RoomsList::draw(sf::RenderWindow &window) const
{
    _disconnect.draw(window);
    _join.draw(window);
    _create.draw(window);
}

bool RoomsList::disconnect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (_disconnect.event(event, window)) {
        socket.close();
        return (false);
    }
    return (true);
}

void RoomsList::update(const sf::Event &event, const sf::RenderWindow &window)
{
}

void RoomsList::event(const sf::Event &event, const sf::RenderWindow &window)
{
    _disconnect.event(event, window);
    _join.event(event, window);
    _create.event(event, window);
}
