/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BOOMRANGBULLETC_HPP__
#define BOOMRANGBULLETC_HPP__

#include "Entity.hpp"

class BoomrangBulletC : public Entity {
public:
    BoomrangBulletC(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed,
                const sf::Color &startColor,
                const sf::Color &endColor,
                int health);
    ~BoomrangBulletC();

    void update() override;
    void drawSprite(sf::RenderWindow &window) override;
    void drawParticles(sf::RenderWindow &window) override;

protected:
private:
};

#endif /* !BOOMRANGBULLETC_HPP__ */