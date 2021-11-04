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

void Window::gameLoop()
{
        sf::Event event;

    while (_window.isOpen()) {
        _window.clear();
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _parallax.drawLayers(&_window);
        _parallax.moveLayers();
        _window.display();
    }
}