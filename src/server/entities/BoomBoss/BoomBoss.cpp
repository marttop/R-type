/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "BoomBoss.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new BoomBoss;
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

BoomBoss::BoomBoss()
    : ServerEntity(CustomRect(326 * 4 / 8, 66 * 4))
{
    int x = std::rand() % 200 + 2000;
    int y = 300;
    setPosition(x, y);
    _speed = -5;
    _health = 180;
    _maxHealth = _health;
    _type = "BoomBoss";
    _loader.loadEntityWithPath("./src/server/entities/BoomrangBullet/BoomrangBullet.so", "BoomrangBullet");
    startClock();
}

BoomBoss::~BoomBoss()
{
}

void BoomBoss::startClock()
{
    _shootClock = clock();
}

bool BoomBoss::checkClock()
{
    clock_t t = (clock() - _shootClock);
    if (((float)t / CLOCKS_PER_SEC) > 0.01) {
        _shootClock = clock();
        return true;
    }
    return false;
}

void BoomBoss::shoot()
{
    static int id = 0;
    std::shared_ptr<IEntity> bullet1 = _loader.createEntityWithName("BoomrangBullet");
   
    bullet1->setId(getId() + std::to_string(id));
    id += 1;

    bullet1->setPosition(getPosition().first, getPosition().second + 142);
    int t = rand() % 4 + -2;
    bullet1->setDirection(-1, t);

    _ammos.push_back(bullet1);
}

void BoomBoss::update()
{
    if (getPosition().first > 1600) {
        setPosition(getPosition().first + _speed, getPosition().second);
    } else {
        if (checkClock()) {
            shoot();
        }
        if (getPosition().second > 600 || getPosition().second < 50) {
            _speed *= -1;
        }
        setPosition(getPosition().first, getPosition().second + _speed);
    }
}