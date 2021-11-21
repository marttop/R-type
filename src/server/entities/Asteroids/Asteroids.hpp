/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Asteroids
*/

#ifndef ASTEROIDS_HPP_
#define ASTEROIDS_HPP_

#include "ServerEntity.hpp"

class Asteroids : public ServerEntity
{
    public:
        Asteroids();
        ~Asteroids();

        void update();

    protected:
    private:
};

#endif /* !ASTEROIDS_HPP_ */
