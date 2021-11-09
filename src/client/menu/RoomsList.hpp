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
#include "SEPParsor.hpp"

class RoomsList {
    public:
        RoomsList();
        ~RoomsList();

        void create(const sf::RectangleShape &background);
        void draw(sf::RenderWindow &window) const;
        void update(char *buf);
        void event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket);
        bool disconnect(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &socket);
        void cleanHover();

    protected:
    private:
        void scrollerEvents(const sf::Event &event, const sf::RenderWindow &window);
        void loadRooms(const std::vector<std::string> &cmd);
        void createRoom(const std::vector<std::string> &cmd);
        void mouseWheelScroll(const sf::Event &event, const sf::RenderWindow &window);
        void deleteRoom(const std::vector<std::string> &cmd);

        Button _disconnect;
        Button _create;
        std::vector<RoomCard *> _rooms;
        sf::RectangleShape _background;
        sf::RectangleShape _scroller;
        std::pair<int, int> _displayedIdx;
        int _thickness;
        int _cardNb;
        sf::Sprite _scrollArrow[2];
        sf::Texture _scrollArrowTexture[2];
        sf::Color _outline;
};

#endif /* !ROOMSLIST_HPP_ */
