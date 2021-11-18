/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <map>
#include <memory>
#include <functional>

#include "EntityFactory.hpp"
#include "WarningBox.hpp"
#include "SEPParsor.hpp"
#include "PlayerShip.hpp"

class Game {
    public:
        Game();
        ~Game();

        enum Direction {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            SPACE
        };

        void create(sf::RenderWindow &window, asio::ip::udp::socket &udpSocket);
        void event(const sf::Event &event, asio::ip::udp::socket &udpSocket);
        void openAlert();
        void setAlert();
        void draw() const;
        void handleRead(const asio::error_code &error);

    protected:
    private:
        void update();
        void udpUpdateEntity(std::vector<std::string> &cmdUdp);
        void inputManagement(const sf::Event &event, asio::ip::udp::socket &udpSocket);
        void selectPlayerColor(std::vector<std::string> &entityCmd, sf::Color &startColor, sf::Color &endColor);

        WarningBox _alert;
        EntityFactory _factory;
        char _udpBuf[1024];
        std::map<std::string, std::shared_ptr<IClientEntity>> _entityMap;
        bool _inputs[5];
        int _playerCount;
        asio::streambuf _message;
        sf::RenderWindow *_window;
        asio::ip::udp::socket *_udpSocket;
};

#endif /* !GAME_HPP_ */
