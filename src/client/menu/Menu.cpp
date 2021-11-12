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

void Menu::create(const sf::RenderWindow &window, char *tcpBuf, char *udpBuf)
{
    _background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 1.5));
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _background.setPosition(sf::Vector2f(window.getSize().x / 2, -_background.getSize().y / 2));

    _animationEnd = false;

    _connection.create(_background);
    _connected = false;
    _animation.restart();

    _tcpBuf = tcpBuf;
    _udpBuf = udpBuf;

    _logoTexture = AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/r_type_logo.png");
    _logo.setTexture(_logoTexture);
    _logo.setOrigin(sf::Vector2f(_logo.getTextureRect().width / 2, _logo.getTextureRect().height / 2));
    _logo.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 1.6));

}

void Menu::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::endpoint &tcpEndpoint, boost::asio::ip::tcp::socket &tcpSocket, boost::asio::ip::udp::socket &udpSocket)
{
    if (!_alert.isOpen() && _animationEnd) {
        if (!_connected) {
            _connection.event(event, window);
            _connection.connect(event, window, tcpEndpoint, tcpSocket, _alert);
            _ip = tcpEndpoint.address().to_string();
        } else if (!_inRoom) {
            _roomsList.event(event, window, tcpSocket);
            _connected = _roomsList.disconnect(event, window, tcpSocket);
        } else {
            _room.event(event, window, tcpSocket, udpSocket);
        }
    } else
        _alert.event(event, window);
}

void Menu::openAlert()
{
    std::string stringBuf(_tcpBuf);
    if (stringBuf.size() > 0 && stringBuf.find("500") != std::string::npos) {
        stringBuf.erase(0, 4);
        if (stringBuf.find('\n') != std::string::npos)
            stringBuf.pop_back();
        _alert.open(stringBuf, true);
    }
}

void Menu::joinRoom(std::vector<std::string> &cmdTcp, boost::asio::ip::udp::endpoint &udpEndpoint, boost::asio::ip::udp::socket &udpSocket)
{
    if (_connected && cmdTcp.size() > 1 && cmdTcp[0] == "230") {
        if (cmdTcp.back().find('\n') != std::string::npos)
            cmdTcp.back().pop_back();
        _inRoom = true;
        _room.setRoom(cmdTcp, udpEndpoint, udpSocket, _ip);
    }
}

void Menu::leaveRoom(boost::asio::ip::udp::socket &udpSocket)
{
    std::string strBuf(_tcpBuf);
    if (strBuf.find('\n') != std::string::npos)
        strBuf.pop_back();
    if (_connected && _inRoom && strBuf.size() > 0 && strBuf == "100") {
        _inRoom = false;
        udpSocket.close();
    }
}

bool Menu::startAnimation(const sf::RenderWindow &window)
{
    if (_animationEnd)
        return (_animationEnd);
    if (_background.getPosition().y < window.getSize().y / 2) {
        _background.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y + 2000 * _animation.getElapsedTime().asSeconds()));
        _logo.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 1.6));
    } else {
        _roomsList.create(_background);
        _room.create(_background);
        _alert.create(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));
        return (true);
    }
    _animation.restart();
    return (false);
}

void Menu::update(const sf::RenderWindow &window, boost::asio::ip::udp::endpoint &udpEndpoint, boost::asio::ip::udp::socket &udpSocket)
{
    _animationEnd = startAnimation(window);
    std::vector<std::string> cmdTcp = SEPParsor::parseCommands(_tcpBuf);
    std::vector<std::string> cmdUdp = SEPParsor::parseCommands(_udpBuf);
    openAlert();
    joinRoom(cmdTcp, udpEndpoint, udpSocket);
    leaveRoom(udpSocket);
    _connection.update(window, _background, _animationEnd);
    _roomsList.update(cmdTcp, window, _connected);
    _room.update(cmdUdp, window);
}

void Menu::setAlert()
{
    _alert.open("Lost connection with the server.", false);
}

void Menu::draw(sf::RenderWindow &window) const
{
    if (!_alert.isOpen()) {
        window.draw(_background);
        window.draw(_logo);
        if (!_connected)
            _connection.draw(window);
        else if (!_inRoom)
            _roomsList.draw(window);
        else
            _room.draw(window);
    }
    _alert.draw(window);
}