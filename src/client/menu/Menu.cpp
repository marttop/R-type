/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
    _socket = nullptr;
    _resolver = nullptr;
}

Menu::~Menu()
{
    if (_socket)
        delete _socket;
    if (_resolver)
        delete _resolver;
}

void Menu::getDefaultInput()
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

void Menu::create(const sf::RenderWindow &window)
{
    _resolver = new boost::asio::ip::tcp::resolver(_io_context);
    _socket = new boost::asio::ip::tcp::socket(_io_context);

    _background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 1.5));
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    getDefaultInput();

    _nameBox.create(sf::Vector2f(_background.getSize().x / 3, _background.getSize().y / 16), sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 5), "Choose your name", _name, false, true);
    _ipBox.create(sf::Vector2f(_background.getSize().x / 3, _background.getSize().y / 16), sf::Vector2f(_background.getPosition().x, _background.getPosition().y), "Server IP", _ip, true, true, false);
    _portBox.create(sf::Vector2f(_background.getSize().x / 3, _background.getSize().y / 16), sf::Vector2f(_background.getPosition().x, _background.getPosition().y + _background.getSize().y / 5), "Server PORT", _port, false, true, false);
    _play.create(sf::Vector2f(_background.getPosition().x, _background.getPosition().y + _background.getSize().y / 2), "Connect");
    _alert.create(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));
}

void Menu::connect(const sf::Event &event, const sf::RenderWindow &window)
{
    if (_play.event(event, window)) {
        _name = _nameBox.getInputString();
        _ip = _ipBox.getInputString();
        _port = _portBox.getInputString();
        if (_name == "")
            _alert.open("Please enter a non empty name.");
        else if (_validator.validateIpAddress(_ip) == 0)
            _alert.open("Please provide a valid ip address.");
        else if (_validator.validatePort(std::atoi(_port.c_str())) == 0)
            _alert.open("Please provide a valid port.");
        else {
            std::ofstream myfile;
            myfile.open ("src/client/menu/save.txt");
            myfile <<  _ip << ";" << _port << ";" << _name;
            myfile.close();
            _endpoint = boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(_ip), (unsigned short)std::atoi(_port.c_str()));
            try {
                _socket->connect(_endpoint);
                _alert.open("Connected.");
            } catch(std::exception& error) {
                //_socket->close();
                _alert.open("Connection refused.");
            }
        }
    }
}

void Menu::event(const sf::Event &event, const sf::RenderWindow &window)
{
    if (!_alert.isOpen()) {
        _nameBox.event(event, window);
        _ipBox.event(event, window);
        _portBox.event(event, window);
        connect(event, window);
    } else
        _alert.event(event, window);
}

void Menu::update()
{
    _nameBox.update();
    _ipBox.update();
    _portBox.update();
}

void Menu::draw(sf::RenderWindow &window) const
{
    if (!_alert.isOpen()) {
        window.draw(_background);
        _nameBox.draw(window);
        _ipBox.draw(window);
        _portBox.draw(window);
        _play.draw(window);
    }
    _alert.draw(window);
}