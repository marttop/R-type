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
    for (auto it : _players)
        delete it;
    _players.clear();
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

    _port = 0;
}

void Room::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (_leave.event(event, window))
        socket.send(boost::asio::buffer("235 " + _id + "\n"));
    _ready.event(event, window);
}

void Room::update(std::vector<std::string> &cmd)
{

}

void Room::setRoom(std::vector<std::string> &cmd)
{
    for (auto it : _players)
        delete it;
    _players.clear();
    _id = cmd[1];
    _port = std::atoi(cmd[2].c_str());
    std::string name;
    std::string isReady;
    int i = 0;
    for (auto it : cmd) {
        if (i < 3) {
            i++;
            continue;
        }
        if (i % 2 == 1)
            name = it;
        else {
            isReady = it;
            _players.push_back(new PlayerCard);
            if (_players.size() == 1)
                _players.back()->create(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2, _background.getPosition().y - _background.getSize().y / 2), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 4), name);
            else
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x, _players.at(_players.size() - 2)->getPosition().y + _players.at(_players.size() - 2)->getSize().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 4), name);
        }
        i++;
    }
}

void Room::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    _leave.draw(window);
    _ready.draw(window);
    for (auto it : _players)
        it->draw(window);
}
