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

    std::memset(_buf, '\0', 1024);
    _resolver = new boost::asio::ip::tcp::resolver(_io_context);
    _socket = new boost::asio::ip::tcp::socket(_io_context);

    _parallax.create(100);
    _menu.create(_window, _buf);
    _scene = MENU;
}

Window::~Window()
{
    if (_socket)
        delete _socket;
    if (_resolver)
        delete _resolver;
}

void Window::event()
{
    if (_event.type == sf::Event::Closed)
        _window.close();
    if (_scene == MENU) {
        //_parallax.event(_event);
        _menu.event(_event, _window, _endpoint, *_socket);
    }
}

void Window::update()
{
    if (_scene == MENU) {
        _parallax.update();
        _menu.update();
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

void Window::read()
{
    if (_socket->is_open()) {
        std::memset(_buf, '\0', 1024);
        _socket->non_blocking(true);
        size_t len = 0;
        len = _socket->receive(boost::asio::buffer(_buf), 0, _error);
        std::cout << _buf;
    }
}

void Window::gameLoop()
{
    while (_window.isOpen()) {
        read();
        while (_window.pollEvent(_event))
            event();
        update();
        draw();
    }
}