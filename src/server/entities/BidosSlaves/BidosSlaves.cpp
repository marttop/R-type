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
}

BidosSlaves::~BidosSlaves()
{
}

void BidosSlaves::update()
{
    std::cout << "tas mére la pute j'update" << std::endl;
}