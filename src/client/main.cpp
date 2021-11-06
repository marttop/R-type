/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** main
*/

#include "Window.hpp"

typedef  int (Window::*func)(void);

int main(void)
{
    Window window("R-TYPE");

    window.gameLoop();

    return EXIT_SUCCESS;
}