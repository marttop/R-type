/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ServerEntity.hpp"

class ServerPlayer : public ServerEntity {
    public:
        ServerPlayer(const CustomRect &rect);
        ~ServerPlayer();

        void update() override;

    protected:
    private:
};

#endif /* !PLAYER_HPP_ */
