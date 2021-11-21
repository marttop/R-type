/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BOOMBOSS_HPP__
#define BOOMBOSS_HPP__

#include "Entity.hpp"
#include "AssetManager.hpp"

class BoomBossC : public Entity {
public:
    BoomBossC(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed,
                const sf::Color &startColor,
                const sf::Color &endColor,
                int health);
    ~BoomBossC();

    void update();
    void updateHp();
    void drawSprite(sf::RenderWindow &window) override;

protected:
private:
    sf::RectangleShape _hpRect;
    sf::RectangleShape _barRect;
    sf::Font _font;
    sf::Text _name;
};

#endif /* !BOOMBOSS_HPP__ */