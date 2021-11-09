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
    for (auto it : _rooms)
        delete it;
    _rooms.clear();
}

void RoomsList::create(const sf::RectangleShape &background)
{
    _create.create(sf::Vector2f(background.getPosition().x + background.getSize().x / 4, background.getPosition().y + background.getSize().y / 2), "Create");
    _disconnect.create(sf::Vector2f(background.getPosition().x - background.getSize().x / 4, background.getPosition().y + background.getSize().y / 2), "Disconnect");

    _outline = sf::Color::White;

    _background.setSize(sf::Vector2f(background.getSize().x / 1.2, background.getSize().y / 1.2));
    _background.setFillColor(sf::Color::Transparent);
    _background.setOutlineColor(_outline);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(background.getPosition().x, background.getPosition().y));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _scroller.setSize(sf::Vector2f(25.0, _background.getSize().y));
    _scroller.setFillColor(sf::Color(0, 0, 0, 255));
    _scroller.setOutlineColor(_outline);
    _scroller.setOutlineThickness(2.0);
    _scroller.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 2 - _scroller.getSize().x / 2, _background.getPosition().y));
    _scroller.setOrigin(sf::Vector2f(_scroller.getSize().x / 2, _scroller.getSize().y / 2));

    _scrollArrowTexture[0].loadFromFile("assets/scroll_arrow_white.png");
    _scrollArrowTexture[1].loadFromFile("assets/scroll_arrow_black.png");

    _scrollArrow[0].setTexture(_scrollArrowTexture[0]);
    _scrollArrow[0].setOrigin(sf::Vector2f(_scrollArrow[0].getTextureRect().width / 2, _scrollArrow[0].getTextureRect().height / 2));
    _scrollArrow[0].setPosition(sf::Vector2f(_scroller.getPosition().x, _scroller.getPosition().y - _scroller.getSize().y / 2 + _scrollArrowTexture[0].getSize().y / 1.5));

    _scrollArrow[1].setTexture(_scrollArrowTexture[0]);
    _scrollArrow[1].setOrigin(sf::Vector2f(_scrollArrow[1].getTextureRect().width / 2, _scrollArrow[1].getTextureRect().height / 2));
    _scrollArrow[1].setPosition(sf::Vector2f(_scroller.getPosition().x, _scroller.getPosition().y + _scroller.getSize().y / 2 - _scrollArrowTexture[0].getSize().y / 1.5));
    _scrollArrow[1].rotate(180.0);

    _cardNb = 8;
    _displayedIdx = std::make_pair(0, _cardNb);
    _thickness = 1.0;
}

void RoomsList::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(_scroller);
    window.draw(_scrollArrow[0]);
    window.draw(_scrollArrow[1]);
    for (int i = 0; i < _rooms.size(); i++) {
        if (i >= _displayedIdx.first && i < _displayedIdx.second)
            _rooms[i]->draw(window);
    }
    _disconnect.draw(window);
    _create.draw(window);
}

bool RoomsList::disconnect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    if (_disconnect.event(event, window)) {
        socket.close();
        _disconnect.cleanHover();
        return (false);
    }
    return (true);
}

void RoomsList::update(char *buf)
{
    std::vector<std::string> cmd = SEPParsor::parseCommands(buf);
    if (cmd.size() == 2 && cmd[0] == "310") {
        std::string roomId = cmd[1];
        if (_rooms.size() == 0) {
            _rooms.push_back(new RoomCard);
            _rooms.back()->create(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2 + _thickness, _background.getPosition().y - _background.getSize().y / 2 - _thickness), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), "Room " + roomId, 0, _thickness);
        } else {
            _rooms.push_back(new RoomCard);
            _rooms.back()->create(sf::Vector2f(_rooms.at(_rooms.size() - 2)->getPosition().x, _rooms.at(_rooms.size() - 2)->getPosition().y + _rooms.at(_rooms.size() - 2)->getSize().y), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), "Room " + roomId, 0, _thickness);
        }
    }
}

void RoomsList::scrollerEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseMoved) {
        if (_scroller.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _outline = sf::Color::Yellow;
            _scroller.setOutlineColor(sf::Color::Yellow);
        }
        else {
            _outline = sf::Color::White;
            _scroller.setOutlineColor(_outline);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_scroller.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _scroller.setFillColor(sf::Color::White);
            if (_scrollArrow[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                _scrollArrow[0].setTexture(_scrollArrowTexture[1]);
                if (_displayedIdx.first > 0) {
                    _displayedIdx.first--;
                    _displayedIdx.second--;
                    for (auto it : _rooms) {
                        it->incrementPosition();
                    }
                }
            }
            else if (_scrollArrow[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                _scrollArrow[1].setTexture(_scrollArrowTexture[1]);
                if (_displayedIdx.second < _rooms.size()) {
                    _displayedIdx.first++;
                    _displayedIdx.second++;
                    for (auto it : _rooms) {
                        it->decrementPosition();
                    }
                }
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        _scroller.setFillColor(sf::Color::Black);
        _scrollArrow[0].setTexture(_scrollArrowTexture[0]);
        _scrollArrow[1].setTexture(_scrollArrowTexture[0]);
        if (_scroller.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _scroller.setOutlineColor(_outline);
        }
    }
}

void RoomsList::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket)
{
    _disconnect.event(event, window);
    if (_create.event(event, window))
        socket.send(boost::asio::buffer("300\n"));
    for (int i = 0; i < _rooms.size(); i++) {
        if (i >= _displayedIdx.first && i < _displayedIdx.second)
            _rooms[i]->event(event, window);
    }
    scrollerEvent(event, window);
}
