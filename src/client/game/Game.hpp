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
#include <SFML/Audio.hpp>

#include "EntityFactory.hpp"
#include "WarningBox.hpp"
#include "SEPParsor.hpp"
#include "PlayerShip.hpp"

#define BUFF_SIZE 65535

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
        bool event(const sf::Event &event, asio::ip::udp::socket &udpSocket);
        void openAlert();
        void setAlert();
        void handleRead(const asio::error_code &error);
        std::thread startThread(const asio::error_code &error, bool &closeGame);
        void draw();
        void stopMusic();
        void startMusic();

    protected:
    private:
        void update();
        bool checkGameOver() const;
        void udpUpdateEntity(std::vector<std::string> &cmdUdp);
        void inputManagement(const sf::Event &event, asio::ip::udp::socket &udpSocket);
        void selectPlayerColor(std::vector<std::string> &entityCmd, sf::Color &startColor, sf::Color &endColor);

        WarningBox _alert;
        EntityFactory _factory;
        char _udpBuf[BUFF_SIZE];
        std::map<std::string, std::shared_ptr<IClientEntity>> _entityMap;
        bool _inputs[5];
        int _playerCount;
        asio::streambuf _message;
        sf::RenderWindow *_window;
        asio::ip::udp::socket *_udpSocket;
        sf::Clock _gameClock;
        bool *_closeGame;
        bool _isGameFinished;
        sf::Music _music;
};

#endif /* !GAME_HPP_ */