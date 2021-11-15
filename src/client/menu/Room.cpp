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

    _background.setSize(sf::Vector2f(background.getSize().x / 1.1, background.getSize().y / 1.3));
    _background.setFillColor(sf::Color::Transparent);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(background.getPosition().x, background.getPosition().y + background.getSize().y / 30));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _counterBox.setFillColor(sf::Color::Black);
    _counterBox.setOutlineColor(sf::Color::White);
    _counterBox.setOutlineThickness(2.0);
    _counterBox.setPosition(sf::Vector2f(background.getPosition().x, background.getPosition().y));

    _counterText.setFont(_font);

    _counter = false;

    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");

    _playerCount.setFont(_font);
    _playerCount.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2.45, background.getPosition().y - background.getSize().y / 2.2));
    _roomName.setFont(_font);
    _roomName.setPosition(sf::Vector2f(background.getPosition().x - background.getSize().x / 2.22, background.getPosition().y - background.getSize().y / 2.2));

    _id = "";

    _port = 0;

    _isReady = 0;
}

void Room::event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket, asio::ip::udp::socket &udpSocket)
{
    if (_leave.event(event, window))
        tcpSocket.send(asio::buffer("235 " + _id + "\n"));
    if (_ready.event(event, window)) {
        _isReady = !_isReady;
        udpSocket.send(asio::buffer("003 " + std::to_string(_isReady) + "\n"));
    }
}

void Room::readyUpdate(std::vector<std::string> &cmdUdp)
{
    if (cmdUdp.size() == 3 && cmdUdp[0] == "004") {
        std::string state = cmdUdp[1];
        std::string name = cmdUdp[2];
        for (auto it : _players) {
            if (it->getName() == name) {
                it->setReady(state);
                if (state == "0" && _counter)
                    _counter = !_counter;
            }
        }
    }
}

void Room::counterUpdate(std::vector<std::string> &cmdUdp)
{
    if (cmdUdp.size() == 2 && cmdUdp[0] == "005") {
        std::string sec = cmdUdp[1];
        sec.pop_back();
        _counterText.setString("Starting in " + sec + " seconds!\n");
        _counterBox.setSize(sf::Vector2f(_counterText.getGlobalBounds().width * 1.5, _counterText.getGlobalBounds().height * 1.5));
        _counterBox.setOrigin(sf::Vector2f(_counterBox.getSize().x / 2, _counterBox.getSize().y / 2));
        _counterText.setOrigin(sf::Vector2f(_counterText.getGlobalBounds().width / 2, _counterText.getGlobalBounds().height / 2));
        _counterText.setPosition(sf::Vector2f(_counterBox.getPosition().x, _counterBox.getPosition().y * 1.025));
        _counter = true;
    }
}

void Room::roomJoin(std::vector<std::string> &cmdUdp)
{
    if (cmdUdp.size() == 2 && cmdUdp[0] == "001") {
        if (cmdUdp.back().find('\n') != std::string::npos)
            cmdUdp.back().pop_back();
        std::string name = cmdUdp[1];
        if (_players.size() < 4) {
            _players.push_back(new PlayerCard);
            if (_players.size() == 2)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x + _players.at(_players.size() - 2)->getSize().x, _players.at(_players.size() - 2)->getPosition().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, "0");
            else if (_players.size() == 3)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 3)->getPosition().x, _players.at(_players.size() - 3)->getPosition().y + _players.at(_players.size() - 3)->getSize().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, "0");
            else if (_players.size() == 4)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x + _players.at(_players.size() - 2)->getSize().x, _players.at(_players.size() - 2)->getPosition().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, "0");
            _playerCount.setString(std::to_string(_players.size()) + "/4");
            if (_counter)
                _counter = !_counter;
        }
    }
}

void Room::roomLeave(std::vector<std::string> &cmdUdp)
{
    if (cmdUdp.size() == 2 && cmdUdp[0] == "002") {
        std::string name = cmdUdp[1];
        if (_players.size() > 1) {
            int i = 0;
            for (auto it : _players) {
                if (it->getName() == name) {
                    _players.erase(_players.begin() + i);
                    _playerCount.setString(std::to_string(_players.size()) + "/4");
                    delete it;
                    break;
                }
                i++;
            }
            i = 0;
            for (auto it : _players) {
                if (i == 0)
                    it->setPosition(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2, _background.getPosition().y - _background.getSize().y / 2));
                else if (i == 1)
                    it->setPosition(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x + _players.at(_players.size() - 2)->getSize().x, _players.at(_players.size() - 2)->getPosition().y));
                else if (i == 2)
                    it->setPosition(sf::Vector2f(_players.at(_players.size() - 3)->getPosition().x, _players.at(_players.size() - 3)->getPosition().y + _players.at(_players.size() - 3)->getSize().y));
                i++;
            }
        }
    }
}

void Room::update(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window)
{
    _leave.update(window);
    _ready.update(window);
    readyUpdate(cmdUdp);
    roomJoin(cmdUdp);
    roomLeave(cmdUdp);
    counterUpdate(cmdUdp);
}

void Room::setRoom(std::vector<std::string> &cmdTcp, asio::ip::udp::endpoint &udpEndpoint, asio::ip::udp::socket &udpSocket, const std::string &ip)
{
    for (auto it : _players)
        delete it;
    _players.clear();
    _id = cmdTcp[1];
    _port = std::atoi(cmdTcp[2].c_str());
    std::string name;
    std::string isReady;
    int i = 0;
    for (auto it : cmdTcp) {
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
                _players.back()->create(sf::Vector2f(_background.getPosition().x - _background.getSize().x / 2, _background.getPosition().y - _background.getSize().y / 2), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, isReady);
            else if (_players.size() == 2)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x + _players.at(_players.size() - 2)->getSize().x, _players.at(_players.size() - 2)->getPosition().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, isReady);
            else if (_players.size() == 3)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 3)->getPosition().x, _players.at(_players.size() - 3)->getPosition().y + _players.at(_players.size() - 3)->getSize().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, isReady);
            else if (_players.size() == 4)
                _players.back()->create(sf::Vector2f(_players.at(_players.size() - 2)->getPosition().x + _players.at(_players.size() - 2)->getSize().x, _players.at(_players.size() - 2)->getPosition().y), sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 6), name, isReady);
        }
        i++;
    }
    _playerCount.setString(std::to_string(_players.size()) + "/4");
    _roomName.setString("Room " + _id);
    udpEndpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(ip), (unsigned short)(_port));
    udpSocket.connect(udpEndpoint);
    udpSocket.send(asio::buffer("connected\n"));
}

void Room::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    _leave.draw(window);
    _ready.draw(window);
    for (auto it : _players)
        it->draw(window);
    window.draw(_playerCount);
    window.draw(_roomName);
    if (_counter) {
        window.draw(_counterBox);
        window.draw(_counterText);
    }
}
