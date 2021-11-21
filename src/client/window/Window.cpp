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
    _udpSocket = new asio::ip::udp::socket(_io_context);

    _parallax.create(100);
    _menu.create(_window, _tcpBuf, _udpBuf);
    _game.create(_window, *_udpSocket);
    _scene = MENU;

    _lostConnection = false;
    _gameStarted = false;
    _closeGame = false;

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
        _closeGame = true;
    if (_scene == GAME) {
        if (_game.event(_event, *_udpSocket)) {
            _scene = MENU;
            std::vector<bool> direction = {1, 0, 0, 1};
            _parallax.setDirection(direction);
            _gameStarted = false;
            _game.create(_window, *_udpSocket);
            _menu.setInRoom(false, *_tcpSocket);
            _udpSocket->close();
        }
    }
    else if (_scene == MENU) {
        //_parallax.event(_event);
        _menu.event(_event, _window, _tcpEndpoint, *_tcpSocket, *_udpSocket);
    }
}


void Window::switchScene()
{
    if (std::strlen(_udpBuf) > 3 && std::strncmp(_udpBuf, "006", 3) == 0) {
        _scene = GAME;
        std::vector<bool> direction = {1, 0, 0, 0};
        _parallax.setDirection(direction);
        std::memset(_udpBuf, '\0', 1024);
    }
}

void Window::update()
{
    switchScene();
    if (_scene == MENU || _scene == GAME) {
        _parallax.update();
        _menu.update(_window, _udpEndpoint, *_udpSocket, _scene);
        if (_scene == MENU) {
            _menu.startMusic();
            _game.stopMusic();
        } else {
            _menu.stopMusic();
            _game.startMusic();
        }
    }
    if (_scene == GAME && !_gameStarted) {
        _udpSocket->non_blocking(false);
        _gameStarted = true;
        std::thread th = _game.startThread(_udpError, _closeGame);
        th.detach();
    }
}

void Window::draw()
{
    _window.clear();
    if (_scene == MENU || _scene == GAME)
        _parallax.draw(_window);
    if (_scene == MENU)
        _menu.draw(_window);
    if (_scene == GAME) {
        _game.draw();
    }
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
        std::cout << _tcpBuf;
    }
}

void Window::readUdp()
{
    if (_lostConnection == false && _udpSocket->is_open() && _scene != GAME) {
        std::memset(_udpBuf, '\0', 1024);
        _udpSocket->non_blocking(true);
        size_t len = 0;
        len = _udpSocket->receive(asio::buffer(_udpBuf), 0, _udpError);
        std::cout << _udpBuf;
    }
}

void Window::gameLoop()
{
    while (_window.isOpen()) {
        if (_closeGame) _window.close();
        readTcp();
        readUdp();
        while (_window.pollEvent(_event))
            event();
        update();
        draw();
    }
}