/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BOSSBULLET_HPP__
#define BOSSBULLET_HPP__

#include "Entity.hpp"
#include "AssetManager.hpp"

class BossBulletC : public Entity {
    public:
        BossBulletC(const sf::Texture &texture,
                    const sf::Vector2f &pos,
                    const float &speed,
                    const sf::Color &startColor,
                    const sf::Color &endColor,
                    int health);
        ~BossBulletC();

        /**
         * @brief Update the BossBulletC
         * 
         * @return ** void 
         */
        void update() override;

        /**
         * @brief Draw the BossBulletC sprite
         * 
         * @param window 
         * @return ** void 
         */
        void drawSprite(sf::RenderWindow &window) override;

        /**
         * @brief Draw the BossBulletC particles
         * 
         * @param window 
         * @return ** void 
         */
        void drawParticles(sf::RenderWindow &window) override;

    protected:
    private:
        sf::SoundBuffer _shootBuf;
        sf::Sound _shoot;
};

#endif /* !BOSSBULLET_HPP__ */