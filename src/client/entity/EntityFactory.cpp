/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** EntityFactory
*/

#include <iostream>
#include "EntityFactory.hpp"

EntityFactory::EntityFactory()
{
    _cmd.emplace("player", &EntityFactory::getPlayer);
}

EntityFactory::~EntityFactory()
{
}

std::shared_ptr<IClientEntity> EntityFactory::getEntityByType
                    (const std::string &type, const sf::Vector2f &pos, const std::string &id)
{
    return (getPlayer(pos, id));
    EntityFactory::factoryF func = _cmd[type];

    return ((this->*func)(pos, id));
}

std::shared_ptr<IClientEntity> EntityFactory::
                getPlayer(const sf::Vector2f &pos, const std::string &id)
{
    std::shared_ptr<IClientEntity> entity(new PlayerShip(AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/scroll_arrow_white.png"), pos, id));
    return (entity);
}

