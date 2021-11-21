/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BIDOSBULLET_HPP__
#define BIDOSBULLET_HPP__

#include "AssetManager.hpp"
#include "Entity.hpp"

class BidosBulletC : public Entity {
    public:
        BidosBulletC(const sf::Texture &texture,
                    const sf::Vector2f &pos,
                    const float &speed,
                    const sf::Color &startColor,
                    const sf::Color &endColor,
                    int health);
        ~BidosBulletC();

        void update() override;
        void drawSprite(sf::RenderWindow &window) override;
        void drawParticles(sf::RenderWindow &window) override;

    protected:
    private:
        sf::SoundBuffer _shootBuf;
        sf::Sound _shoot;
};

#endif /* !BIDOSBULLET_HPP__ */