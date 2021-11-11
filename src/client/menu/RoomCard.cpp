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

void RoomCard::create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &id, const int &users, const double &thickness, const sf::Vector2f &factors)
{
    _outline = sf::Color::White;

    _thickness = thickness;

    _background.setSize(sf::Vector2f(size.x - _thickness * 2, size.y - _thickness * 2));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(_outline);
    _background.setOutlineThickness(_thickness);
    _background.setPosition(sf::Vector2f(pos.x, pos.y + _thickness * 2));

    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");

    _id = id;

    _title.setString("Room " + _id);
    _title.setScale(factors);
    _title.setFont(_font);
    _title.setOrigin(sf::Vector2f(_title.getOrigin().x, _title.getGlobalBounds().height / 3));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 1.9));

    _playerCount.setString(std::to_string(users) + "/4\n");
    _playerCount.setScale(factors);
    _playerCount.setFont(_font);
    _playerCount.setOrigin(sf::Vector2f(_playerCount.getOrigin().x, _playerCount.getGlobalBounds().height / 3));
    _playerCount.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 1.35, _background.getPosition().y + _background.getSize().y / 1.9));

    _delete.create(sf::Vector2f(_background.getPosition().x + _background.getSize().x - _background.getSize().x / 10, _background.getPosition().y + _background.getSize().y / 2), "Delete", sf::Vector2f(-10, -5), sf::Vector2f(0.7, 0.7));
}

void RoomCard::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(_title);
    window.draw(_playerCount);
    _delete.draw(window);
}

std::string RoomCard::getId() const
{
    std::string formattedId = _id;
    formattedId.pop_back();
    return (formattedId);
}

sf::Vector2f RoomCard::getPosition() const
{
    return (_background.getPosition());
}

void RoomCard::incrementPosition()
{
    _background.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y + _background.getSize().y + _thickness * 2));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 2));
    _playerCount.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 1.35, _background.getPosition().y + _background.getSize().y / 1.9));
    _delete.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x - _background.getSize().x / 10, _background.getPosition().y + _background.getSize().y / 2));
}

void RoomCard::decrementPosition()
{
    _background.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y - _thickness * 2));
    _title.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 20, _background.getPosition().y + _background.getSize().y / 2));
    _playerCount.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 1.35, _background.getPosition().y + _background.getSize().y / 1.9));
    _delete.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x - _background.getSize().x / 10, _background.getPosition().y + _background.getSize().y / 2));
}

sf::Vector2f RoomCard::getSize() const
{
    return (_background.getSize());
}

void RoomCard::decrementPlayer()
{
    std::string count = _playerCount.getString();
    if (count[0] == '0')
        return;
    count[0]--;
    _playerCount.setString(count);
}

void RoomCard::incrementPlayer()
{
    std::string count = _playerCount.getString();
    if (count[0] == '4')
        return;
    count[0]++;
    _playerCount.setString(count);
}

void RoomCard::update(const sf::RenderWindow &window)
{
    if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        _outline = sf::Color::Yellow;
        _background.setOutlineColor(_outline);
    }
    else {
        _outline = sf::Color::White;
        _background.setOutlineColor(_outline);
    }
}

void RoomCard::join(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (!_delete.isMouseHovering(window)) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                _background.setFillColor(sf::Color::White);
                _title.setFillColor(sf::Color::Black);
                _playerCount.setFillColor(sf::Color::Black);
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            _background.setFillColor(sf::Color::Black);
            _title.setFillColor(sf::Color::White);
            _playerCount.setFillColor(sf::Color::White);
            if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                socket.send(boost::asio::buffer("225 " + _id + "\n"));
        }
    }
}

void RoomCard::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (_delete.event(event, window))
        socket.send(boost::asio::buffer("350 " + _id + "\n"));
    join(event, window, socket);
}
