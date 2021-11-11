/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#include "Window.hpp"

Window::Window(const std::string &title)
{
    _window.create(sf::VideoMode::getDesktopMode(), title);
    _window.setFramerateLimit(60);

    std::memset(_tcpBuf, '\0', 1024);
    std::memset(_udpBuf, '\0', 1024);
    _resolver = new boost::asio::ip::tcp::resolver(_io_context);
    _tcpSocket = new boost::asio::ip::tcp::socket(_io_context);
    _udpSocket = new boost::asio::ip::udp::socket(_io_context);

    _parallax.create(100);
    _menu.create(_window, _tcpBuf, _udpBuf);
    _scene = MENU;

    _lostConnection = false;
}

Window::~Window()
{
    if (_tcpSocket)
        delete _tcpSocket;
    if (_resolver)
        delete _resolver;
}

void Window::event()
{
    if (_event.type == sf::Event::Closed)
        _window.close();
    if (_scene == MENU) {
        //_parallax.event(_event);
        _menu.event(_event, _window, _tcpEndpoint, *_tcpSocket, *_udpSocket);
    }
}

void Window::update()
{
    if (_scene == MENU) {
        _parallax.update();
        _menu.update(_window, _udpEndpoint, *_udpSocket);
    }
}

void Window::draw()
{
    _window.clear();
    if (_scene == MENU) {
        _parallax.draw(_window);
        _menu.draw(_window);
    }
    _window.display();
}

void Window::readTcp()
{
    if (_tcpError == boost::asio::error::eof) {
        _menu.setAlert();
        _tcpError.clear();
    } else if (_lostConnection == false && _tcpSocket->is_open()) {
        std::memset(_tcpBuf, '\0', 1024);
        _tcpSocket->non_blocking(true);
        size_t len = 0;
        len = _tcpSocket->receive(boost::asio::buffer(_tcpBuf), 0, _tcpError);
        std::cout << _tcpBuf;
    }
}

void Window::readUdp()
{
    if (_lostConnection == false && _udpSocket->is_open()) {
        std::memset(_udpBuf, '\0', 1024);
        _udpSocket->non_blocking(true);
        size_t len = 0;
        len = _udpSocket->receive(boost::asio::buffer(_udpBuf), 0, _udpError);
        std::cout << _udpBuf;
    }
}

void Window::gameLoop()
{
    while (_window.isOpen()) {
        readTcp();
        readUdp();
        while (_window.pollEvent(_event))
            event();
        update();
        draw();
    }
}