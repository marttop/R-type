/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include <SFML/Graphics.hpp>
#include <asio.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "InputBox.hpp"
#include "Button.hpp"
#include "ValidateIp.hpp"
#include "WarningBox.hpp"

class Connection {
    public:
        Connection();
        ~Connection();

    /**
     * @brief Create Connection
     * 
     * @param background 
     * @return ** void 
     */
    void create(const sf::RectangleShape &background);

    /**
     * @brief Connection events
     * 
     * @param event 
     * @param window 
     * @return ** void 
     */
    void event(const sf::Event &event, const sf::RenderWindow &window);

    /**
     * @brief Update Connection
     * 
     * @param window 
     * @param background 
     * @param animationEnd 
     * @param isDrawn 
     * @return ** void 
     */
    void update(const sf::RenderWindow &window, const sf::RectangleShape &background, const bool &animationEnd, const bool &isDrawn);

    /**
     * @brief Draw Connection
     * 
     * @param window 
     * @return ** void 
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Connect event
     * 
     * @param event 
     * @param window 
     * @param endpoint 
     * @param socket 
     * @param alert 
     * @return ** void 
     */
    void connect(const sf::Event &event, const sf::RenderWindow &window, asio::ip::tcp::endpoint &endpoint, asio::ip::tcp::socket &socket, WarningBox &alert);

    protected:
    private:
        void getDefaultInput();

        InputBox _nameBox;
        InputBox _ipBox;
        InputBox _portBox;
        Button _connect;
        ValidateIp _validator;
        std::string _ip;
        std::string _name;
        std::string _port;
};

#endif /* !CONNECTION_HPP_ */
