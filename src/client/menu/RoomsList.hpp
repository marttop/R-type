/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RoomsList
*/

#ifndef ROOMSLIST_HPP_
#define ROOMSLIST_HPP_

#include <SFML/Graphics.hpp>

class RoomsList {
    public:
        RoomsList();
        ~RoomsList();

        void create(const sf::RenderWindow &window);
        void draw(sf::RenderWindow &window) const;
        void update(const sf::Event &event, const sf::RenderWindow &window);

    protected:
    private:
};

#endif /* !ROOMSLIST_HPP_ */
