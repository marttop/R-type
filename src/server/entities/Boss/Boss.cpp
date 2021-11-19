/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "Boss.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new Boss;
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

Boss::Boss()
    : ServerEntity(CustomRect(512 * 4 / 8, 132 * 4))
{
    int x = std::rand() % 200 + 2000;
    int y = 300;
    setPosition(x, y);
    _speed = -10;
    _health = 200;
    _maxHealth = _health;
    _type = "Boss";
    _loader.loadEntityWithPath("./src/server/entities/BossBullet/BossBullet.so", "BossBullet");
    startClock();
}

Boss::~Boss()
{
}

void Boss::startClock()
{
    _shootClock = clock();
}

bool Boss::checkClock()
{
    clock_t t = (clock() - _shootClock);
    if (((float)t / CLOCKS_PER_SEC) > 0.05) {
        _shootClock = clock();
        return true;
    }
    return false;
}

void Boss::shoot()
{
    static int id = 0;
    std::shared_ptr<IEntity> bullet1 = _loader.createEntityWithName("BossBullet");
    std::shared_ptr<IEntity> bullet2 = _loader.createEntityWithName("BossBullet");
    std::shared_ptr<IEntity> bullet3 = _loader.createEntityWithName("BossBullet");
   
    bullet1->setId(getId() + std::to_string(id));
    id += 1;
    bullet2->setId(getId() + std::to_string(id));
    id += 1;
    bullet3->setId(getId() + std::to_string(id));
    id += 1;

    bullet1->setPosition(getPosition().first, getPosition().second + 142);
    bullet2->setPosition(getPosition().first, getPosition().second + 142);
    bullet3->setPosition(getPosition().first, getPosition().second + 142);

    bullet1->setDirection(1, 3);
    bullet2->setDirection(1, 0);
    bullet3->setDirection(1, -3);

    _ammos.push_back(bullet1);
    _ammos.push_back(bullet2);
    _ammos.push_back(bullet3);
}

void Boss::update()
{
    if (getPosition().first > 1700) {
        setPosition(getPosition().first + _speed, getPosition().second);
    } else {
        if (checkClock()) {
            shoot();
        }
        if (getPosition().second > 500 || getPosition().second < 50) {
            _speed *= -1;
        }
        setPosition(getPosition().first, getPosition().second + _speed);
    }
}