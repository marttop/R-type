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
    _parallax.create(200, Parallax::DOWN);
    _menu.create(_window);
    _scene = MENU;
}

Window::~Window()
{
}

void Window::parallaxDirection()
{
    if (_scene == MENU) {
        if (_event.key.code == sf::Keyboard::Down)
            _parallax.setDirection(Parallax::DOWN);
        if (_event.key.code == sf::Keyboard::Left)
            _parallax.setDirection(Parallax::LEFT);
        if (_event.key.code == sf::Keyboard::Right)
            _parallax.setDirection(Parallax::RIGHT);
        if (_event.key.code == sf::Keyboard::Up)
            _parallax.setDirection(Parallax::UP);
    }
}

void Window::event()
{
    if (_event.type == sf::Event::Closed)
        _window.close();
    if (_event.type == sf::Event::KeyPressed)
        parallaxDirection();
}

void Window::update()
{
    if (_scene == MENU) {
        _parallax.move();
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