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
    : ServerEntity(CustomRect(20, 20))
{
    setPosition(1800, std::rand() % 900 + 100);
    _speed = -3;
    _type = "BidosSlaves";
}

BidosSlaves::~BidosSlaves()
{
}

void BidosSlaves::update()
{
    setPosition(getPosition().first + _speed, getPosition().second);
}