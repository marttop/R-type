/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>

#include "Button.hpp"

class Room {
    public:
        Room();
        ~Room();

        void create(const sf::RectangleShape &background);
        void event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket);
        void update();
        void draw(sf::RenderWindow &window) const;
        void setId(const std::string &id);

    protected:
    private:
        sf::RectangleShape _background;
        Button _leave;
        Button _ready;
        std::string _id;
};

#endif /* !ROOM_HPP_ */
