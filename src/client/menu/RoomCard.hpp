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

        /**
         * @brief Create RoomCard
         * 
         * @param pos 
         * @param size 
         * @param text 
         * @param users 
         * @param thickness 
         * @param factors 
         * @return ** void 
         */
        void create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text, const int &users = 0, const double &thickness = 1.0, const sf::Vector2f &factors = {1, 1});

        /**
         * @brief Draw RoomCard
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;

        /**
         * @brief RoomCard events
         * 
         * @param event 
         * @param window 
         * @param socket 
         * @return true 
         * @return false 
         */
        bool event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::socket &socket);

        /**
         * @brief Get the Position object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getPosition() const;

        /**
         * @brief Get the Size object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getSize() const;

        /**
         * @brief Increment RoomCard position
         * 
         * @return ** void 
         */
        void incrementPosition();

        /**
         * @brief Decrement RoomCard position
         * 
         * @return ** void 
         */
        void decrementPosition();

        /**
         * @brief Update RoomCard
         * 
         * @param window 
         * @param isDrawn 
         * @return ** void 
         */
        void update(const sf::RenderWindow &window, const bool &isDrawn);

        /**
         * @brief Get the Id object
         * 
         * @return ** std::string 
         */
        std::string getId() const;

        /**
         * @brief Increment RoomCard players
         * 
         * @return ** void 
         */
        void incrementPlayer();

        /**
         * @brief Decrement RoomCard players
         * 
         * @return ** void 
         */
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
