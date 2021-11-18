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

    _background.setSize(sf::Vector2f(background.getSize().x / 1.1, background.getSize().y / 1.2));
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

    _scrollArrowTexture[0] = AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/scroll_arrow_white.png");
    _scrollArrowTexture[1] = AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/scroll_arrow_black.png");

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

bool RoomsList::disconnect(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket)
{
    if (_disconnect.event(event, window)) {
        tcpSocket.close();
        for (auto it : _rooms)
            delete it;
        _rooms.clear();
        _displayedIdx.first = 0;
        _displayedIdx.second = _cardNb;
        return (false);
    }
    return (true);
}

void RoomsList::loadRooms(const std::vector<std::string> &cmd, bool &connected)
{
    if (cmd.size() > 0 && (cmd[0] == "220" || cmd[0] == "220\n")) {
        bool check = false;
        std::string roomId;
        std::string playerCount;
        for (auto it : cmd) {
            if (it == cmd.front()) continue;
            if (check == false) roomId = it, check = true;
            else playerCount = it, check = false;
            if (check == false) {
                if (_rooms.size() == 0) {
                    _rooms.push_back(new RoomCard);
                    _rooms.back()->create(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2 + _thickness, _background.getPosition().y - _background.getSize().y / 2 - _thickness), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), roomId + "\n", std::atoi(playerCount.c_str()), _thickness);
                } else {
                    _rooms.push_back(new RoomCard);
                    _rooms.back()->create(sf::Vector2f(_rooms.at(_rooms.size() - 2)->getPosition().x, _rooms.at(_rooms.size() - 2)->getPosition().y + _rooms.at(_rooms.size() - 2)->getSize().y), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), roomId + "\n", std::atoi(playerCount.c_str()), _thickness);
                }
            }
        }
        connected = true;
    }
}

void RoomsList::createRoom(const std::vector<std::string> &cmd)
{
    if (cmd.size() == 2 && cmd[0] == "310") {
        std::string roomId = cmd[1];
        if (_rooms.size() == 0) {
            _rooms.push_back(new RoomCard);
            _rooms.back()->create(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2 + _thickness, _background.getPosition().y - _background.getSize().y / 2 - _thickness), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), roomId, 0, _thickness);
        } else {
            _rooms.push_back(new RoomCard);
            _rooms.back()->create(sf::Vector2f(_rooms.at(_rooms.size() - 2)->getPosition().x, _rooms.at(_rooms.size() - 2)->getPosition().y + _rooms.at(_rooms.size() - 2)->getSize().y), sf::Vector2f(_background.getSize().x - _scroller.getSize().x - _thickness * 2, _background.getSize().y / _cardNb), roomId, 0, _thickness);
        }
    }
}

void RoomsList::deleteRoom(const std::vector<std::string> &cmd)
{
    if (cmd.size() == 2 && cmd[0] == "380") {
        std::string roomId = cmd[1];
        if (roomId.size() > 0 && roomId.find('\n') != std::string::npos)
            roomId.pop_back();
        RoomCard *to_delete = nullptr;
        bool check = false;
        for (int i = 0; i < _rooms.size(); i++) {
            if (!check && _rooms[i]->getId() == roomId) {
                to_delete = _rooms[i];
                _rooms.erase(_rooms.begin() + i);
                check = true;
            }
            if (check)
                _rooms[i]->decrementPosition();
        }
        if (to_delete)
            delete to_delete;
    }
}

void RoomsList::userJoinedRoom(const std::vector<std::string> &cmd)
{
    if (cmd.size() == 2 && cmd[0] == "280") {
        std::string roomId = cmd[1];
        roomId.pop_back();
        for (auto it : _rooms) {
            if (it->getId() == roomId) {
                it->incrementPlayer();
                break;
            }
        }
    }
}

void RoomsList::userLeftRoom(const std::vector<std::string> &cmd)
{
    if (cmd.size() > 0 && cmd[0] == "290") {
        if (cmd[1] == "\n")
            return;
        std::string roomId = cmd[1];
        roomId.pop_back();
        for (auto it : _rooms) {
            if (it->getId() == roomId) {
                it->decrementPlayer();
                break;
            }
        }
    }
}

void RoomsList::scrollerUpdate(const sf::RenderWindow &window)
{
    if (_scroller.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        _outline = sf::Color::Yellow;
        _scroller.setOutlineColor(sf::Color::Yellow);
    }
    else {
        _outline = sf::Color::White;
        _scroller.setOutlineColor(_outline);
    }
}

void RoomsList::update(std::vector<std::string> &cmdTcp, const sf::RenderWindow &window, bool &connected)
{
    scrollerUpdate(window);
    _disconnect.update(window);
    _create.update(window);
    loadRooms(cmdTcp, connected);
    createRoom(cmdTcp);
    deleteRoom(cmdTcp);
    userJoinedRoom(cmdTcp);
    userLeftRoom(cmdTcp);
    for (auto it : _rooms)
        it->update(window);
}

void RoomsList::scrollerEvents(const sf::Event &event, const sf::RenderWindow &window)
{
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

void RoomsList::mouseWheelScroll(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseWheelScrolled && _background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if (event.mouseWheelScroll.delta > 0) {
            if (_displayedIdx.first > 0) {
                _displayedIdx.first--;
                _displayedIdx.second--;
                for (auto it : _rooms)
                    it->incrementPosition();
            }
        } else if (event.mouseWheelScroll.delta < 0) {
            if (_displayedIdx.second < _rooms.size()) {
                _displayedIdx.first++;
                _displayedIdx.second++;
                for (auto it : _rooms)
                    it->decrementPosition();
            }
        }
    }
}

void RoomsList::event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket)
{
    if (_create.event(event, window))
        tcpSocket.send(asio::buffer("300\n"));
    for (int i = 0; i < _rooms.size(); i++) {
        if (i >= _displayedIdx.first && i < _displayedIdx.second)
            _rooms[i]->event(event, window, tcpSocket);
    }
    scrollerEvents(event, window);
    mouseWheelScroll(event, window);
}
