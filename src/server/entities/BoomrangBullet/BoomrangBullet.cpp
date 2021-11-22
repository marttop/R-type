/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "BoomrangBullet.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new BoomrangBullet;
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

BoomrangBullet::BoomrangBullet()
    : ServerEntity(CustomRect(398 * 4 / 8, 30 * 4))
{
    int x = 0;
    int y = 0;
    setPosition(x, y);
    _speed = 8;
    _health = 1;
    _maxHealth = _health;
    _type = "BoomrangBullet";

    _isPlayerHarmful = true;
}

BoomrangBullet::~BoomrangBullet()
{
}

void BoomrangBullet::update()
{

    if (getPosition().first < -50 || getPosition().second > 1400 || getPosition().second < -50) {
        _isAlive = false;
    }
    setPosition(getPosition().first + _direction.first * _speed, getPosition().second + _direction.second);

    if (_direction.first < 1) {
        _direction.first += 0.003;
    }

    if (_direction.second > -1) {
        _direction.second -= 0.008;
    }
}