/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "BossBullet.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new BossBullet;
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


// La Position negatif pcq pendant une frame on ne sais pas ou est la balle

BossBullet::BossBullet()
    : ServerEntity(CustomRect(102 * 4 / 3, 34 * 4))
{
    int x = 0;
    int y = 0;
    setPosition(x, y);
    _maxHealth = _health;
    _speed = 10;
    _type = "BossBullet";
}

BossBullet::~BossBullet()
{
}

void BossBullet::update()
{
    if (getPosition().first < -50 || getPosition().second > 1400 || getPosition().second < -50) {
        _isAlive = false;
    }
    setPosition(getPosition().first - _direction.first * _speed, getPosition().second + _direction.second);
}