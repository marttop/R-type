/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Connection
*/

#include "Connection.hpp"

Connection::Connection()
{
}

Connection::~Connection()
{
}

void Connection::create(const sf::RectangleShape &background)
{
    getDefaultInput();

    _nameBox.create(sf::Vector2f(background.getSize().x / 3, background.getSize().y / 16), sf::Vector2f(background.getPosition().x, background.getPosition().y - background.getSize().y / 5), "Choose your name", _name, false, true);
    _ipBox.create(sf::Vector2f(background.getSize().x / 3, background.getSize().y / 16), sf::Vector2f(background.getPosition().x, background.getPosition().y), "Server IP", _ip, true, true, false);
    _portBox.create(sf::Vector2f(background.getSize().x / 3, background.getSize().y / 16), sf::Vector2f(background.getPosition().x, background.getPosition().y + background.getSize().y / 5), "Server PORT", _port, false, true, false);
    _connect.create(sf::Vector2f(background.getPosition().x, background.getPosition().y + background.getSize().y / 2), "Connect");
}

bool Connection::connect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::endpoint &endpoint, boost::asio::ip::tcp::socket &socket, WarningBox &alert)
{
    if (_connect.event(event, window)) {
        _name = _nameBox.getInputString();
        _ip = _ipBox.getInputString();
        _port = _portBox.getInputString();
        if (_name == "")
            alert.open("Please enter a non empty name.", true);
        else if (_validator.validateIpAddress(_ip) == 0)
            alert.open("Please provide a valid ip address.", true);
        else if (_validator.validatePort(std::atoi(_port.c_str())) == 0)
            alert.open("Please provide a valid port.", true);
        else {
            std::ofstream myfile;
            myfile.open ("src/client/menu/save.txt");
            myfile <<  _ip << ";" << _port << ";" << _name;
            myfile.close();
            endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(_ip), (unsigned short)std::atoi(_port.c_str()));
            try {
                socket.connect(endpoint);
                socket.send(boost::asio::buffer("210 " + _name + "\n"));
                _connect.cleanHover();
                return (true);
            } catch(std::exception& error) {
                socket.close();
                alert.open("Connection refused.", true);
            }
        }
    }
    return (false);
}

void Connection::getDefaultInput()
{
    std::string line;
    std::ifstream saveFile ("src/client/menu/save.txt");
    if (saveFile.is_open()) {
        std::getline(saveFile, line);
        _ip = line.substr(0, line.find(";"));
        if (_ip == "")
            _ip = "192.168.0.0";
        line.erase(0, _ip.size() + 1);
        _port = line.substr(0, line.find(";"));
        if (_port == "")
            _port = "8888";
        line.erase(0, _port.size() + 1);
        _name = line;
        if (_name == "")
            _name = "Player";
        saveFile.close();
    }
    else {
        _ip = "192.168.0.0";
        _name = "Player";
        _port = "8888";
        std::ofstream newFile ("src/client/menu/save.txt");
        newFile << _ip << ";" << _port << ";" << _name;
        newFile.close();
    }
}

void Connection::event(const sf::Event &event, const sf::RenderWindow &window)
{
    _nameBox.event(event, window);
    _ipBox.event(event, window);
    _portBox.event(event, window);
}

void Connection::update()
{
    _nameBox.update();
    _ipBox.update();
    _portBox.update();
}

void Connection::draw(sf::RenderWindow &window) const
{
    _nameBox.draw(window);
    _ipBox.draw(window);
    _portBox.draw(window);
    _connect.draw(window);
}