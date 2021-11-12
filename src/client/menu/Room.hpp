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
#include <vector>

#include "Button.hpp"
#include "PlayerCard.hpp"

class Room {
    public:
        Room();
        ~Room();

        void create(const sf::RectangleShape &background);
        void event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::socket &tcpSocket, boost::asio::ip::udp::socket &udpSocket);
        void update(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window);
        void draw(sf::RenderWindow &window) const;
        void setRoom(std::vector<std::string> &cmdTcp, boost::asio::ip::udp::endpoint &udpEndpoint, boost::asio::ip::udp::socket &udpSocket, const std::string &ip);

    protected:
    private:
        void readyUpdate(std::vector<std::string> &cmdUdp);
        void roomJoin(std::vector<std::string> &cmdUdp);
        void roomLeave(std::vector<std::string> &cmdUdp);
        void counterUpdate(std::vector<std::string> &cmdUdp);

        int _port;
        sf::RectangleShape _background;
        Button _leave;
        Button _ready;
        std::string _id;
        std::vector<PlayerCard *> _players;
        sf::Text _playerCount;
        sf::Text _roomName;
        sf::RectangleShape _counterBox;
        sf::Text _counterText;
        sf::Font _font;
        int _isReady;
        bool _counter;
};

#endif /* !ROOM_HPP_ */
