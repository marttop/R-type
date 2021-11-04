/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Window {
    public:
        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        sf::Window _window;
};

#endif /* !WINDOW_HPP_ */
