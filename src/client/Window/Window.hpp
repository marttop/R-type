/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include "Parallax.hpp"

class Window {
    public:
        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        void event();
        void update();
        void draw();

        sf::RenderWindow _window;
        sf::Event _event;
        Parallax _parallax;
};

#endif /* !WINDOW_HPP_ */
