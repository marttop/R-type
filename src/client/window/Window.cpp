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
    _window.setFramerateLimit(70);

    std::memset(_tcpBuf, '\0', 1024);
    std::memset(_udpBuf, '\0', 1024);
    _resolver = new asio::ip::tcp::resolver(_io_context);
    _tcpSocket = new asio::ip::tcp::socket(_io_context);
    _udpWriteSocket = new asio::ip::udp::socket(_io_context);

    _parallax.create(100);
    _menu.create(_window, _tcpBuf, _udpBuf);
    _game.create(_window, _udpBuf);
    _scene = MENU;

    _lostConnection = false;

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(7);
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
    if (_scene == GAME)
        _game.event(_event, _window);
    if (_scene == MENU) {
        //_parallax.event(_event);
        _menu.event(_event, _window, _tcpEndpoint, *_tcpSocket, *_udpWriteSocket);
    }
}


void Window::switchScene()
{
    if (std::strlen(_udpBuf) > 3 && std::strncmp(_udpBuf, "006", 3) == 0) {
        _scene = GAME;
        std::vector<bool> direction = {1, 0, 0, 0};
        _parallax.setDirection(direction);
    }
}

void Window::update()
{
    switchScene();
    if (_scene == MENU || _scene == GAME)
        _parallax.update();
    if (_scene == MENU)
        _menu.update(_window, _udpEndpoint, *_udpWriteSocket, *_udpReadSocket);
    if (_scene == GAME)
        _game.update(_window, *_udpWriteSocket);
}

void Window::draw()
{
    _window.clear();
    if (_scene == MENU || _scene == GAME)
        _parallax.draw(_window);
    if (_scene == MENU)
        _menu.draw(_window);
    if (_scene == GAME)
        _game.draw(_window);
    _window.display();
}

void Window::readTcp()
{
    if (_tcpError == asio::error::eof) {
        _menu.setAlert();
        _game.setAlert();
        _tcpError.clear();
    } else if (_lostConnection == false && _tcpSocket->is_open()) {
        std::memset(_tcpBuf, '\0', 1024);
        _tcpSocket->non_blocking(true);
        size_t len = 0;
        len = _tcpSocket->receive(asio::buffer(_tcpBuf), 0, _tcpError);
        //std::cout << _tcpBuf;
    }
}

void Window::readUdp()
{
    if (_lostConnection == false && _udpWriteSocket->is_open()) {
        if (!_udpReadSocket->is_open()) {
            _udpReadSocket->connect(asio::ip::udp::endpoint(_udpWriteSocket->remote_endpoint().address(), _udpWriteSocket->remote_endpoint().port() + 1));
            _udpReadSocket->send(asio::buffer("read connected\n"));
        }
        std::memset(_udpBuf, '\0', 1024);
        _udpWriteSocket->non_blocking(true);
        size_t len = 0;
        len = _udpWriteSocket->receive(asio::buffer(_udpBuf), 0, _udpError);
        //std::cout << _udpBuf;
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