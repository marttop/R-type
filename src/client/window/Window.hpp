/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <asio.hpp>

#include "Parallax.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "RtypeException.hpp"

class Window {
    public:
        enum Scene {
            MENU,
            GAME,
        };

        Window(const std::string &title);
        ~Window();

        void gameLoop();

    protected:
    private:
        void event();
        void update();
        void draw();
        void readTcp();
        void readUdp();
        void switchScene();
        void handleRead(const asio::error_code &error);

        sf::RenderWindow _window;
        sf::Event _event;
        Parallax _parallax;
        Menu _menu;
        Game _game;
        Scene _scene;
        bool _lostConnection;
        bool _gameStarted;

        asio::io_context _io_context;
        asio::ip::tcp::resolver *_resolver;
        asio::ip::tcp::socket *_tcpSocket;
        asio::ip::udp::socket *_udpSocket;
        char _tcpBuf[1024];
        char _udpBuf[1024];
        asio::error_code _tcpError;
        asio::error_code _udpError;
        std::mutex _lock;
        asio::ip::tcp::endpoint _tcpEndpoint;
        asio::ip::udp::endpoint _udpEndpoint;
};

#endif /* !WINDOW_HPP_ */
