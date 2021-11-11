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

        void create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name, const std::string &ready, const sf::Vector2f &factors = {1, 1});
        void draw(sf::RenderWindow &window) const;
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        std::string getName() const;
        void setReady(const std::string &state);

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
