/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>

#include "WarningBox.hpp"
#include "Connection.hpp"
#include "RoomsList.hpp"
#include "Room.hpp"

class Menu {
    public:
        Menu();
        ~Menu();


        void create(const sf::RenderWindow &window, char *tcpBuf, char *udpBuf);
        void draw(sf::RenderWindow &window) const;
        void event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::tcp::endpoint &tcpEndpoint, boost::asio::ip::tcp::socket &tcpSocket, boost::asio::ip::udp::socket &udpSocket);
        void update(const sf::RenderWindow &window, boost::asio::ip::udp::endpoint &udpEndpoint, boost::asio::ip::udp::socket &udpSocket);
        void setAlert();

    protected:
    private:
        void connect(const sf::Event &event, const sf::RenderWindow &window);
        void getDefaultInput();
        void joinRoom(std::vector<std::string> &cmdTcp, boost::asio::ip::udp::endpoint &udpEndpoint, boost::asio::ip::udp::socket &udpSocket);
        void openAlert();
        void leaveRoom(boost::asio::ip::udp::socket &udpSocket);

        sf::RectangleShape _background;
        WarningBox _alert;
        Connection _connection;
        RoomsList _roomsList;
        bool _connected;
        bool _inRoom;
        sf::Texture _logoTexture;
        sf::Sprite _logo;
        char *_tcpBuf;
        char *_udpBuf;
        Room _room;
        std::string _ip;
        sf::Clock _animation;
};

#endif /* !MENU_HPP_ */
