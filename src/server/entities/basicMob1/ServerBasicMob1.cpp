/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServerBasicMob1
*/

#include "ServerBasicMob1.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" IEntity *allocator()
{
    return new ServerBasicMob1;
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

ServerBasicMob1::ServerBasicMob1()
    : ServerEntity(CustomRect(20, 20))
{
}

ServerBasicMob1::~ServerBasicMob1()
{
}

void ServerBasicMob1::update()
{
    std::cout << "tas mére la pute j'update" << std::endl;
}