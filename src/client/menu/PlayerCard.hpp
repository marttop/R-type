/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerCard
*/

#ifndef PLAYERCARD_HPP_
#define PLAYERCARD_HPP_

#include <SFML/Graphics.hpp>

#include "AssetManager.hpp"

class PlayerCard {
    public:
        PlayerCard();
        ~PlayerCard();

        /**
         * @brief Create PlayerCard
         * 
         * @param pos 
         * @param size 
         * @param name 
         * @param ready 
         * @param factors 
         * @return ** void 
         */
        void create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name, const std::string &ready, const sf::Vector2f &factors = {1, 1});

        /**
         * @brief Draw PlayerCard
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;

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
         * @brief Get the Name object
         * 
         * @return ** std::string 
         */
        std::string getName() const;

        /**
         * @brief Set the Ready object
         * 
         * @param state 
         * @return ** void 
         */
        void setReady(const std::string &state);

        /**
         * @brief Set the Position object
         * 
         * @param pos 
         * @return ** void 
         */
        void setPosition(const sf::Vector2f &pos);

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text _name;
        sf::Font _font;
        sf::Texture _readyTexture;
        sf::Texture _notReadyTexture;
        sf::Sprite _ready;
};

#endif /* !PLAYERCARD_HPP_ */
