/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include "PlayerShip.hpp"
#include "AssetManager.hpp"
#include "Bullet.hpp"
#include "BidosSlave.hpp"
#include "BossC.hpp"
#include "Heal.hpp"
#include "BossBulletC.hpp"

#include <memory>

class EntityFactory {
    public:
        EntityFactory();
        ~EntityFactory();

        std::shared_ptr<IClientEntity> getEntityByType(const std::string &type,
                                                        const sf::Vector2f &pos,
                                                        const float &speed,
                                                        const sf::Color &startColor = sf::Color::White,
                                                        const sf::Color &endColor = sf::Color::White,
                                                        int health = 10);


    protected:
    private:
        std::shared_ptr<IClientEntity> getPlayer(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getHeal(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBullet(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBidosSlaves(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBoss(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBossBullet(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        typedef std::shared_ptr<IClientEntity> (EntityFactory::*factoryF) (const sf::Vector2f &pos,
                                                                            const float &speed,
                                                                            const sf::Color &startColor,
                                                                            const sf::Color &endColor,
                                                                            int health);


        // std::shared_ptr<IClientEntity> getBoss(const sf::Vector2f &pos,
        //                                                 const float &speed, const sf::Color &startColor, const sf::Color &endColor);
        std::map<std::string, factoryF> _cmd;
};

#endif /* !ENTITYFACTORY_HPP_ */
