/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <vector>

#include "Button.hpp"
#include "PlayerCard.hpp"

class Room {
    public:
        Room();
        ~Room();

        /**
         * @brief Create Room
         * 
         * @param background 
         * @return ** void 
         */
        void create(const sf::RectangleShape &background);

        /**
         * @brief Room events
         * 
         * @param event 
         * @param window 
         * @param tcpSocket 
         * @param udpSocket 
         * @return ** void 
         */
        void event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &tcpSocket, asio::ip::udp::socket &udpSocket);

        /**
         * @brief Update Room
         * 
         * @param cmdUdp 
         * @param window 
         * @param isDrawn 
         * @return ** void 
         */
        void update(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window, const bool &isDrawn);

        /**
         * @brief Draw Room
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;

        /**
         * @brief Set the Room object
         * 
         * @param cmdTcp 
         * @param udpEndpoint 
         * @param udpSocket 
         * @param ip 
         * @return ** void 
         */
        void setRoom(std::vector<std::string> &cmdTcp, asio::ip::udp::endpoint &udpEndpoint, asio::ip::udp::socket &udpSocket, const std::string &ip);

        /**
         * @brief Get the Room Id object
         * 
         * @return ** std::string 
         */
        std::string getRoomId() const;

    protected:
    private:
        void readyUpdate(std::vector<std::string> &cmdUdp);
        void roomJoin(std::vector<std::string> &cmdUdp);
        void roomLeave(std::vector<std::string> &cmdUdp);
        void counterUpdate(std::vector<std::string> &cmdUdp);

        int _port;
        sf::RectangleShape _background;
        Button _leaving;
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
        sf::Sound _timer;
        sf::SoundBuffer _timerBuf;
};

#endif /* !ROOM_HPP_ */
