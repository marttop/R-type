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

        void create(const sf::RenderWindow &window, char *udpBuf);
        void event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::udp::socket &udpSocket);
        void openAlert();
        void update(const sf::RenderWindow &window, asio::ip::udp::socket &udpSocket);
        void setAlert();
        void draw(sf::RenderWindow &window) const;

    protected:
    private:
        void udpUpdateEntity(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window);
        void inputManagement(const sf::Event &event, asio::ip::udp::socket &udpSocket);
        void sendInput(asio::ip::udp::socket &udpSocket);
        void selectPlayerColor(std::vector<std::string> &entityCmd, sf::Color &startColor, sf::Color &endColor);

        WarningBox _alert;
        EntityFactory _factory;
        char *_udpBuf;
        std::map<std::string, std::shared_ptr<IClientEntity>> _entityMap;
        bool _direction[4];
        bool _shoot;
        int _playerCount;
};

#endif /* !GAME_HPP_ */
