/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** EntityFactory
*/

#include "EntityFactory.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
EntityFactory::EntityFactory()
{
    _cmd.emplace("player", &EntityFactory::getPlayer);
    _cmd.emplace("playerbullet", &EntityFactory::getBullet);
    _cmd.emplace("BidosSlaves", &EntityFactory::getBidosSlaves);
    _cmd.emplace("Boss", &EntityFactory::getBoss);
}

EntityFactory::~EntityFactory()
{
}

std::shared_ptr<IClientEntity> EntityFactory::getEntityByType(const std::string &type,
                                                                const sf::Vector2f &pos,
                                                                const float &speed,
                                                                const sf::Color &startColor,
                                                                const sf::Color &endColor,
                                                                int health)
{
    EntityFactory::factoryF func = _cmd[type];

    return ((this->*func)(pos, speed, startColor, endColor, health));
}

std::shared_ptr<IClientEntity> EntityFactory::getPlayer(const sf::Vector2f &pos,
                                                        const float &speed,
                                                        const sf::Color &startColor,
                                                        const sf::Color &endColor,
                                                        int health)
{
    std::shared_ptr<IClientEntity> entity(new PlayerShip(AssetManager<sf::Texture>::getAssetManager().getAsset("assets/game/ship.png"),
    pos, speed, startColor, endColor, health));

    return (entity);
}

std::shared_ptr<IClientEntity> EntityFactory::getBullet(const sf::Vector2f &pos,
                                                        const float &speed,
                                                        const sf::Color &startColor,
                                                        const sf::Color &endColor,
                                                        int health)
{
    (void)health;
    std::shared_ptr<IClientEntity> entity(new Bullet(AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/scroll_arrow_white.png"),
    pos, speed, startColor, endColor));

    return (entity);
}

std::shared_ptr<IClientEntity> EntityFactory::getBidosSlaves(const sf::Vector2f &pos,
                                                                const float &speed,
                                                                const sf::Color &startColor,
                                                                const sf::Color &endColor,
                                                                int health)
{
    std::shared_ptr<IClientEntity> entity(new BidosSlave(AssetManager<sf::Texture>::getAssetManager().getAsset("assets/game/BidosSlave.png"),
    pos, speed, startColor, endColor, health));

    return (entity);
}

std::shared_ptr<IClientEntity> EntityFactory::getBoss(const sf::Vector2f &pos, const float &speed, const sf::Color &startColor, const sf::Color &endColor)
{
    std::cout << "SPAW BOSS" << std::endl;
    std::shared_ptr<IClientEntity> entity(new BossC(AssetManager<sf::Texture>::getAssetManager().getAsset("assets/game/Boss.png"), pos, speed, startColor, endColor));
    return (entity);
}