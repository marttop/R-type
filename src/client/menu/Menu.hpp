/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sys/types.h>

#include "InputBox.hpp"
#include "Button.hpp"
#include "ValidateIp.hpp"
#include "WarningBox.hpp"

class Menu {
    public:
        Menu();
        ~Menu();

        void create(const sf::RenderWindow &window);
        void draw(sf::RenderWindow &window) const;
        void event(const sf::Event &event, const sf::RenderWindow &window);
        void update();

    protected:
    private:
        void connect(const sf::Event &event, const sf::RenderWindow &window);
        void getDefaultInput();

        sf::RectangleShape _background;
        InputBox _nameBox;
        InputBox _ipBox;
        InputBox _portBox;
        Button _play;
        ValidateIp _validator;
        std::string _ip;
        std::string _name;
        std::string _port;
        WarningBox _alert;

        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::resolver *_resolver;
        boost::asio::ip::tcp::socket *_socket;
        boost::array<char, 128> _buf;
        boost::system::error_code _error;
        boost::asio::ip::tcp::endpoint _endpoint;
};

#endif /* !MENU_HPP_ */
