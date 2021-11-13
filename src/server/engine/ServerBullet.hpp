/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerBullet
*/

#ifndef SERVERBULLET_HPP_
#define SERVERBULLET_HPP_

#include "ServerEntity.hpp"

class ServerBullet : public ServerEntity {
    public:
        ServerBullet(const CustomRect &customRect,
                        const std::string &type,
                        const std::string &id,
                        int health = -1,
                        int speed = 30);
        ~ServerBullet();

        void update();

    protected:
    private:
};

#endif /* !SERVERBULLET_HPP_ */
