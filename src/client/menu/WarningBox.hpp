/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** WarningBox
*/

#ifndef WARNINGBOX_HPP_
#define WARNINGBOX_HPP_

#include <SFML/Graphics.hpp>

#include "Button.hpp"

class WarningBox {
    public:
        WarningBox();
        ~WarningBox();

        /**
         * @brief Create WarningBox
         * 
         * @param pos 
         * @param factors 
         * @return ** void 
         */
        void create(const sf::Vector2f &pos, const sf::Vector2f &factors = {1, 1});

        /**
         * @brief Draw WarningBox
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;

        /**
         * @brief WarningBox events
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        bool event(const sf::Event &event, const sf::RenderWindow &window);

        /**
         * @brief Open WarningBox
         * 
         * @param text 
         * @param isButton 
         * @return ** void 
         */
        void open(const std::string &text, const bool &isButton);

        /**
         * @brief Return WarningBox state
         * 
         * @return true 
         * @return false 
         */
        bool isOpen() const;

        /**
         * @brief Update WarningBox
         * 
         * @param window 
         * @return ** void 
         */
        void update(const sf::RenderWindow &window);

        /**
         * @brief Close WarningBox
         * 
         * @return ** void 
         */
        void close();

    protected:
    private:
        sf::RectangleShape _background;
        sf::Text *_text;
        sf::Font _font;
        Button _close;
        bool _isOpen;
        bool _isButton;
        sf::Vector2f _factors;
};

#endif /* !WARNINGBOX_HPP_ */
