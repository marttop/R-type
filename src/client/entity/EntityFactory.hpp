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
#include "Asteroids.hpp"
#include "BidosBulletC.hpp"
#include "BoomBossC.hpp"
#include "BoomrangBulletC.hpp"

#include <memory>
#include <SFML/Audio.hpp>

class EntityFactory {
    public:
        EntityFactory();
        ~EntityFactory();

        /**
         * @brief Get the Entity By Type object
         * 
         * @param type 
         * @param pos 
         * @param speed 
         * @param startColor 
         * @param endColor 
         * @param health 
         * @return ** std::shared_ptr<IClientEntity> 
         */
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

        std::shared_ptr<IClientEntity> getAsteroids(const sf::Vector2f &pos,
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

        std::shared_ptr<IClientEntity> getBidosBullet(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBoomBoss(const sf::Vector2f &pos,
                                                    const float &speed,
                                                    const sf::Color &startColor,
                                                    const sf::Color &endColor,
                                                    int health);

        std::shared_ptr<IClientEntity> getBoomrangBullet(const sf::Vector2f &pos,
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
