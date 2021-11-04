/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "parallax/Parallax.hpp"
#include <iostream>

class Window {
    public:
        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        sf::RenderWindow _window;
        Parallax _parallax;
};

#endif /* !WINDOW_HPP_ */
