/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.hpp"

class Button {
    public:
        Button();
        ~Button();

        /**
         * @brief Create Button
         * 
         * @param pos 
         * @param text 
         * @param offset 
         * @param factors 
         * @return ** void 
         */
        void create(const sf::Vector2f &pos, const std::string &text, const sf::Vector2f &offset = {0, 0}, const sf::Vector2f &factors = {1, 1});

        /**
         * @brief Draw Button
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;
        
        /**
         * @brief Button events
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        bool event(const sf::Event &event, const sf::RenderWindow &window);

        /**
         * @brief Return hovering state
         * 
         * @param window 
         * @return true 
         * @return false 
         */
        bool isMouseHovering(const sf::RenderWindow &window) const;

        /**
         * @brief Set the Position object
         * 
         * @param pos 
         * @return ** void 
         */
        void setPosition(const sf::Vector2f &pos);

        /**
         * @brief Update Button
         * 
         * @param window 
         * @param isDrawn 
         * @return true 
         * @return false 
         */
        bool update(const sf::RenderWindow &window, const bool &isDrawn);

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text *_text;
        sf::Font _font;
        sf::Color _outline;
        sf::Vector2f _offset;
        sf::Sound _click;
        sf::SoundBuffer _clickBuf;
        sf::Sound _hover;
        sf::SoundBuffer _hoverBuf;
};

#endif /* !BUTTON_HPP_ */
