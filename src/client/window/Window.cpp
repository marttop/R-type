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
    _parallax.create(100);
    _menu.create(_window);
    _scene = MENU;
}

Window::~Window()
{
}

void Window::event()
{
    if (_event.type == sf::Event::Closed)
        _window.close();
    if (_scene == MENU) {
        //_parallax.event(_event);
        _menu.event(_event, _window);
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

void Window::gameLoop()
{
    while (_window.isOpen()) {
        while (_window.pollEvent(_event))
            event();
        update();
        draw();
    }
}