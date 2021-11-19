/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#ifndef SERVERBASICMOB1_HPP_
#define SERVERBASICMOB1_HPP_

#include "ServerEntity.hpp"

class BossBullet : public ServerEntity
{
public:
    BossBullet();
    ~BossBullet();

    void update();

protected:
private:
};

#endif /* !SERVERBASICMOB1_HPP_ */