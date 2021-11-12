/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <map>
#include <memory>

#include "WarningBox.hpp"
#include "SEPParsor.hpp"
#include "PlayerShip.hpp"

class Game {
    public:
        Game();
        ~Game();

        void create(const sf::RenderWindow &window, char *udpBuf);
        void event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::udp::socket &udpSocket);
        void openAlert();
        void update(const sf::RenderWindow &window, boost::asio::ip::udp::socket &udpSocket);
        void setAlert();
        void draw(sf::RenderWindow &window) const;

    protected:
    private:
        void updateEntity(std::vector<std::string> &cmdUdp);

        WarningBox _alert;
        char *_udpBuf;
        std::map<std::string, std::shared_ptr<IClientEntity>> _entityMap;
};

#endif /* !GAME_HPP_ */
