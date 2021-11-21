/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#ifndef BOS_HPP__
#define BOS_HPP__

#include "ServerEntity.hpp"
#include "EntityLoad.hpp"
#include <time.h>

class BoomBoss : public ServerEntity
{
public:
    BoomBoss();
    ~BoomBoss();

    void update();

    void shoot();

    void startClock();
    bool checkClock();

protected:
private:
    EntityLoad _loader;
    clock_t  _shootClock;
};

#endif /* !BOS_HPP__ */