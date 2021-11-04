/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerShip
*/

#ifndef PLAYERSHIP_HPP_
#define PLAYERSHIP_HPP_

#include "../interface/IEntity.hpp"

class PlayerShip : virtual public IEntity {
    public:
        PlayerShip(const std::string &path);
        ~PlayerShip();
        void update() {};
        void sendData() {};

    protected:
    private:
};

#endif /* !PLAYERSHIP_HPP_ */
