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

void Menu::create(const sf::RenderWindow &window, char *buf)
{
    _background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 1.5));
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _connection.create(_background);
    _alert.create(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));

    _connected = false;

    _buf = buf;

    _rooms.create(_background);

    _logoTexture.loadFromFile("assets/r_type_logo.png");
    _logo.setTexture(_logoTexture);
    _logo.setOrigin(sf::Vector2f(_logo.getTextureRect().width / 2, _logo.getTextureRect().height / 2));
    _logo.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 1.6));
}

void Menu::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::endpoint &endpoint, boost::asio::ip::tcp::socket &socket)
{
    if (!_alert.isOpen()) {
        if (!_connected) {
            _connection.event(event, window);
            _connected = _connection.connect(event, window, endpoint, socket, _alert);
        } else {
            _rooms.event(event, window, socket);
            _connected = _rooms.disconnect(event, window, socket);
        }
    } else
        _alert.event(event, window);
}

void Menu::update()
{
    std::string stringBuf(_buf);
    if (stringBuf.size() > 0 && stringBuf.find("500") != std::string::npos) {
        stringBuf.erase(0, 4);
        if (stringBuf.find('\n') != std::string::npos)
            stringBuf.pop_back();
        _alert.open(stringBuf);
    }
    _connection.update();
    _rooms.update(_buf);
}

void Menu::draw(sf::RenderWindow &window) const
{
    if (!_alert.isOpen()) {
        window.draw(_background);
        window.draw(_logo);
        if (!_connected)
            _connection.draw(window);
        else
            _rooms.draw(window);
    }
    _alert.draw(window);
}