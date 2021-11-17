/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServeurMobSpawnConf
*/

#include "ServerMobSpawnConf.hpp"

ServerMobSpawnConf::ServerMobSpawnConf(const std::string type, int timeSpawn, int numberSpawn)
    :   _TypeEnities(type), _time(timeSpawn), _numberOfEntities(numberSpawn)
{
}

ServerMobSpawnConf::~ServerMobSpawnConf()
{
}

int ServerMobSpawnConf::getTimeToSpawn() const
{
    return _time;
}

std::string ServerMobSpawnConf::getTypeEntities() const
{
    return _TypeEnities;
}

int ServerMobSpawnConf::getNumberOfEntities() const
{
    return _numberOfEntities;
}