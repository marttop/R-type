/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "BidosBullet.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new BidosBullet;
}
#endif

// #ifdef WIN32
// extern "C"
// {
// 	__declspec (dllexport) ServerBasicMob1 *allocator()
// 	{
// 		return new ServerBasicMob1();
// 	}

// 	__declspec (dllexport) void deleter(ServerBasicMob1 *ptr)
// 	{
// 		delete ptr;
// 	}
// }
// #endif

BidosBullet::BidosBullet()
    : ServerEntity(CustomRect(149 * 4 / 8, 6 * 4))
{
    int x = 0;
    int y = 0;
    setPosition(x, y);
    _speed = -8;
    _health = 1;
    _maxHealth = _health;
    _type = "BidosBullet";

    _isPlayerHarmful = true;
    _isMobHarmful = true;
}

BidosBullet::~BidosBullet()
{
}

void BidosBullet::update()
{
    if (getPosition().first < -50 || getPosition().second > 1400 || getPosition().second < -50) {
        _isAlive = false;
    }
    setPosition(getPosition().first + _speed, getPosition().second);
}