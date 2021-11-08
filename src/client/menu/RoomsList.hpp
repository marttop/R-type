/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomsList
*/

#ifndef ROOMSLIST_HPP_
#define ROOMSLIST_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <vector>

#include "Button.hpp"
#include "RoomCard.hpp"

class RoomsList {
    public:
        RoomsList();
        ~RoomsList();

        void create(const sf::RectangleShape &background);
        void draw(sf::RenderWindow &window) const;
        void update(const sf::Event &event, const sf::RenderWindow &window);
        void event(const sf::Event &event, const sf::RenderWindow &window);
        bool disconnect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket);
        void scrollerEvent(const sf::Event &event, const sf::RenderWindow &window);

    protected:
    private:
        Button _disconnect;
        Button _join;
        Button _create;
        std::vector<RoomCard *> _rooms;
        sf::RectangleShape _background;
        sf::RectangleShape _scroller;
        std::pair<int, int> _displayedIdx;
        int _thickness;
        sf::Sprite _scrollArrow[2];
        sf::Texture _scrollArrowTexture[2];
        sf::Color _outline;
};

#endif /* !ROOMSLIST_HPP_ */
