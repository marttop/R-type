/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomsList
*/

#ifndef ROOMSLIST_HPP_
#define ROOMSLIST_HPP_

#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <vector>

#include "Button.hpp"
#include "RoomCard.hpp"
#include "SEPParsor.hpp"

class RoomsList {
    public:
        RoomsList();
        ~RoomsList();

        void create(const sf::RectangleShape &background);
        void setIp(const std::string &ip);
        void draw(sf::RenderWindow &window) const;
        void update(std::vector<std::string> &cmdTcp, const sf::RenderWindow &window, bool &connected);
        void event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket);
        bool disconnect(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket);

    protected:
    private:
        void scrollerEvents(const sf::Event &event, const sf::RenderWindow &window);
        void loadRooms(const std::vector<std::string> &cmdTcp, bool &connected);
        void createRoom(const std::vector<std::string> &cmdTcp);
        void mouseWheelScroll(const sf::Event &event, const sf::RenderWindow &window);
        void deleteRoom(const std::vector<std::string> &cmdTcp);
        void userJoinedRoom(const std::vector<std::string> &cmdTcp);
        void userLeftRoom(const std::vector<std::string> &cmdTcp);
        void scrollerUpdate(const sf::RenderWindow &window);

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
