/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>

class Window {
    public:
        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        void event();

        sf::RenderWindow _window;
        sf::Event _event;
};

#endif /* !WINDOW_HPP_ */
