/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Parallax.hpp"
#include "Menu.hpp"

class Window {
    public:
        enum Scene {
            MENU,
        };

        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        void event();
        void update();
        void draw();
        void read();

        sf::RenderWindow _window;
        sf::Event _event;
        Parallax _parallax;
        Menu _menu;
        Scene _scene;

        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::resolver *_resolver;
        boost::asio::ip::tcp::socket *_socket;
        boost::array<char, 1024> _buf;
        boost::system::error_code _error;
        boost::asio::ip::tcp::endpoint _endpoint;
};

#endif /* !WINDOW_HPP_ */
