/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BOSSBULLET_HPP__
#define BOSSBULLET_HPP__

#include "Entity.hpp"

class BossBulletC : public Entity {
public:
    BossBulletC(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed,
                const sf::Color &startColor,
                const sf::Color &endColor,
                int health);
    ~BossBulletC();

    void update() override;
    void drawSprite(sf::RenderWindow &window) override;
    void drawParticles(sf::RenderWindow &window) override;

protected:
private:
};

#endif /* !BOSSBULLET_HPP__ */