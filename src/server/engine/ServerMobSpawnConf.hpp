/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ServeurMobSpawnConf
*/

#ifndef SERVEURMOBSPAWNCONF_HPP_
#define SERVEURMOBSPAWNCONF_HPP_

#include <iostream>
/**
 * @brief this class create with conf file a spawn conf object wich let you 
 * get for room the type, the number and when you need to spawn mob
 * 
 */
class ServerMobSpawnConf {
public:
    /**
     * @brief dedede
     * 
     * @param type          type of Mob to spawn
     * @param timeSpawn     when the mob spawn in second
     * @param numberSpawn   number of time the entities spawn
     */
    ServerMobSpawnConf(const std::string type, int timeSpawn, int numberSpawn);
    ~ServerMobSpawnConf();

    /**
     * @brief Get the Time To Spawn object in seconds
     * 
     * @return ** int
     */
    int                 getTimeToSpawn() const;

    /**
     * @brief Get the Type Entities object
     * 
     * @return ** const std::string 
     */
    const std::string   getTypeEntities() const;

    /**
     * @brief Get the Number Of Entities object
     * 
     * @return ** int 
     */
    int                 getNumberOfEntities() const;

protected:
private:
    const std::string   &_TypeEnities;
    int                 _time;
    int                 _numberOfEntities;
};

#endif /* !SERVEURMOBSPAWNCONF_HPP_ */