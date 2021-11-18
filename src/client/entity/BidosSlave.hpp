/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BIDOSSLAVES_HPP_
#define BIDOSSLAVES_HPP_

#include "Entity.hpp"

class BidosSlave : public Entity {
public:
    BidosSlave(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed,
                const sf::Color &startColor,
                const sf::Color &endColor,
                int health);
    ~BidosSlave();

    void update() override;
    void drawSprite(sf::RenderWindow &window) override;
    void drawParticles(sf::RenderWindow &window) override;

protected:
private:
};

#endif /* !BIDOSSLAVES_HPP_ */