/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** InputBox
*/

#ifndef INPUTBOX_HPP_
#define INPUTBOX_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.hpp"

class InputBox {
    public:
        InputBox();
        ~InputBox();

        /**
         * @brief Create InputBox
         * 
         * @param size 
         * @param pos 
         * @param title 
         * @param defaultInput 
         * @param ip 
         * @param num 
         * @param alpha 
         * @param factors 
         * @return ** void 
         */
        void create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title = "", const std::string &defaultInput = "", const bool &ip = false, const bool &num = false, const bool &alpha = true, const sf::Vector2f &factors = {1, 1});

        /**
         * @brief Draw InputBox
         * 
         * @param window 
         * @return ** void 
         */
        void draw(sf::RenderWindow &window) const;

        /**
         * @brief InputBox events
         * 
         * @param event 
         * @param window 
         * @return ** void 
         */
        void event(const sf::Event &event, const sf::RenderWindow &window);

        /**
         * @brief Update InputBox
         * 
         * @param window 
         * @param isDrawn 
         * @return ** void 
         */
        void update(const sf::RenderWindow &window, const bool &isDrawn);

        /**
         * @brief Set the Position object
         * 
         * @param pos 
         * @return ** void 
         */
        void setPosition(const sf::Vector2f &pos);

        /**
         * @brief Get the Input String object
         * 
         * @return ** std::string 
         */
        std::string getInputString() const;

    protected:
    private:
        sf::RectangleShape _background;
        sf::RectangleShape _cursor;
        sf::Clock _cursorClock;
        std::string _title;
        sf::Text _titleText;
        std::string _input;
        sf::Text _inputText;
        sf::Font _font;
        sf::Color _outline;
        bool _isFocus;
        bool _ip;
        bool _num;
        bool _alpha;
        sf::Sound _click;
        sf::SoundBuffer _clickBuf;
        sf::Sound _hover;
        sf::SoundBuffer _hoverBuf;
};

#endif /* !INPUTBOX_HPP_ */
