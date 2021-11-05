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
}

Window::~Window()
{
}

void Window::event()
{
    if (_event.type == sf::Event::Closed)
        _window.close();
}

void Window::update()
{
    _parallax.move();
}

void Window::draw()
{
    _window.clear();
    _parallax.draw(_window);
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