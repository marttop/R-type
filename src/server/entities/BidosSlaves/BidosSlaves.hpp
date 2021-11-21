/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#ifndef SERVERBASICMOB1_HPP_
#define SERVERBASICMOB1_HPP_

#include "ServerEntity.hpp"
#include "EntityLoad.hpp"
#include <time.h>

class BidosSlaves : public ServerEntity
{
public:
    BidosSlaves();
    ~BidosSlaves();

    void update();

    void startClock();
    bool checkClock();

    void shoot();

protected:
private:
    EntityLoad _loader;
    clock_t _shootClock;
};

#endif /* !SERVERBASICMOB1_HPP_ */