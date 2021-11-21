/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** BidosSlaves
*/

#ifndef BOSS_HPP
#define BOSS_HPP

#include "Entity.hpp"
#include "AssetManager.hpp"

class BossC : public Entity {
public:
    BossC(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed,
                const sf::Color &startColor,
                const sf::Color &endColor,
                int health);
    ~BossC();

    /**
     * @brief Update the BossC
     * 
     * @return ** void 
     */
    void update();

    /**
     * @brief Update the BossC hp
     * 
     * @return ** void 
     */
    void updateHp();

    /**
     * @brief Draw the BossC sprite
     * 
     * @param window 
     * @return ** void 
     */
    void drawSprite(sf::RenderWindow &window) override;

protected:
private:
    sf::RectangleShape _hpRect;
    sf::RectangleShape _barRect;
    sf::Font _font;
    sf::Text _name;
    sf::SoundBuffer _spawnBuf;
    sf::Sound _spawn;
};

#endif /* !BOSS_HPP */