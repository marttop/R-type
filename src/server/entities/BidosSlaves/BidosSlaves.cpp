/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "BidosSlaves.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new BidosSlaves;
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

BidosSlaves::BidosSlaves()
    : ServerEntity(CustomRect(205 * 4 / 12, 18 * 4))
{
    int x = std::rand() % 200 + 2000;
    int y = std::rand() % 1000;
    setPosition(x, y);
    _speed = -3;
    _health = 1;
    _maxHealth = _health;
    _type = "BidosSlaves";
    _loader.loadEntityWithPath("./src/server/entities/BidosBullet/BidosBullet.so", "BidosBullet");
    _hasAClock = true;

    _isDropping = true;
    _isMobHarmful = true;
}

BidosSlaves::~BidosSlaves()
{
}

void BidosSlaves::startClock()
{
    _shootClock = clock();
}

bool BidosSlaves::checkClock()
{
    clock_t t = (clock() - _shootClock);
    if (((float)t / CLOCKS_PER_SEC) > 2 * *_threadCount) {
        _shootClock = clock();
        return true;
    }
    return false;
}

void BidosSlaves::shoot()
{
    static int id = 0;
    std::shared_ptr<IEntity> bullet1 = _loader.createEntityWithName("BidosBullet");
   
    bullet1->setId(getId() + std::to_string(id));
    id += 1;

    bullet1->setPosition(getPosition().first, getPosition().second + 10);

    _ammos.push_back(bullet1);
}

void BidosSlaves::update()
{
    if (getPosition().first < -50) {
        _isAlive = false;
        return;
    }
    if (checkClock()) {
        shoot();
    }
    setPosition(getPosition().first + _speed, getPosition().second);
}