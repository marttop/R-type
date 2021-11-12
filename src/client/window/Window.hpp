/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>

#include "Parallax.hpp"
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

        sf::RenderWindow _window;
        sf::Event _event;
        Parallax _parallax;
        Menu _menu;
        Scene _scene;
        bool _lostConnection;
        std::string _playerId;

        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::resolver *_resolver;
        boost::asio::ip::tcp::socket *_tcpSocket;
        boost::asio::ip::udp::socket *_udpSocket;
        char _tcpBuf[1024];
        char _udpBuf[1024];
        boost::system::error_code _tcpError;
        boost::system::error_code _udpError;
        boost::asio::ip::tcp::endpoint _tcpEndpoint;
        boost::asio::ip::udp::endpoint _udpEndpoint;
};

#endif /* !WINDOW_HPP_ */
