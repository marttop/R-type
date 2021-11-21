/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomCard
*/

#ifndef ROOMCARD_HPP_
#define ROOMCARD_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <asio.hpp>

#include "Button.hpp"

class RoomCard {
    public:
        RoomCard();
        ~RoomCard();

        void create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text, const int &users = 0, const double &thickness = 1.0, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        bool event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &socket);
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        void incrementPosition();
        void decrementPosition();
        void update(const sf::RenderWindow &window, const bool &isDrawn);
        std::string getId() const;
        void incrementPlayer();
        void decrementPlayer();

    protected:
    private:
        void join(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &socket);

        sf::RectangleShape _background;
        sf::Color _outline;
        sf::Text _title;
        sf::Text _playerCount;
        std::string _id;
        sf::Font _font;
        Button _delete;
        double _thickness;
        sf::Sound _click;
        sf::SoundBuffer _clickBuf;
        sf::Sound _hover;
        sf::SoundBuffer _hoverBuf;
};

#endif /* !ROOMCARD_HPP_ */
