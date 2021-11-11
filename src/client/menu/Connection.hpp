/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "InputBox.hpp"
#include "Button.hpp"
#include "ValidateIp.hpp"
#include "WarningBox.hpp"

class Connection {
    public:
        Connection();
        ~Connection();

    void create(const sf::RectangleShape &background);
    void event(const sf::Event &event, const sf::RenderWindow &window);
    void update(const sf::RenderWindow &window);
    void draw(sf::RenderWindow &window) const;
    bool connect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::endpoint &endpoint, boost::asio::ip::tcp::socket &socket, WarningBox &alert);

    protected:
    private:
        void getDefaultInput();

        InputBox _nameBox;
        InputBox _ipBox;
        InputBox _portBox;
        Button _connect;
        ValidateIp _validator;
        std::string _ip;
        std::string _name;
        std::string _port;
};

#endif /* !CONNECTION_HPP_ */
