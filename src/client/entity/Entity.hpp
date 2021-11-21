/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include "IClientEntity.hpp"
#include "Particles.hpp"

class Entity : public IClientEntity {
    public:
        Entity(const sf::Texture &texture,
                const sf::Vector2f &pos,
                const float &speed = 0,
                const sf::Color &startColor = sf::Color::White,
                const sf::Color &endColor = sf::Color::White,
                int health = 10);
        ~Entity();

        /**
         * @brief Get the Elapsed Time object
         * 
         * @return ** float 
         */
        float getElapsedTime() const;

        /**
         * @brief Get the Pos object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getPos() const;

        /**
         * @brief Get the Size object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getSize() const;

        /**
         * @brief Get the Local Bounds object
         * 
         * @return ** sf::FloatRect 
         */
        sf::FloatRect getLocalBounds() const;

        /**
         * @brief Get the Global Bounds object
         * 
         * @return ** sf::FloatRect 
         */
        sf::FloatRect getGlobalBounds() const;

        /**
         * @brief Set the Pos object
         * 
         * @param pos 
         * @return ** void 
         */
        void setPos(const sf::Vector2f &pos);

        /**
         * @brief Set the Rotation object
         * 
         * @param angle 
         * @return ** void 
         */
        void setRotation(const float &angle);

        /**
         * @brief Set the Color object
         * 
         * @param color 
         * @return ** void 
         */
        void setColor(const sf::Color &color);

        /**
         * @brief Restart entity clocks
         * 
         * @return ** void 
         */
        void restartClock();

        /**
         * @brief Get isAlive state
         * 
         * @return true 
         * @return false 
         */
        bool isAlive() const;

        /**
         * @brief Set the Is Alive object
         * 
         * @param isAlive 
         * @return ** void 
         */
        void setIsAlive(bool isAlive);

        /**
         * @brief Get deathFinish state
         * 
         * @return true 
         * @return false 
         */
        bool isDeathFinish() const;

        /**
         * @brief Draw the entity particles
         * 
         * @param window 
         * @return ** void 
         */
        void drawParticles(sf::RenderWindow &window);

        /**
         * @brief Draw the entity sprite
         * 
         * @param window 
         * @return ** void 
         */
        void drawSprite(sf::RenderWindow &window);

        /**
         * @brief Update the entity
         * 
         * @return ** void 
         */
        void update();

        /**
         * @brief Set the Health object
         * 
         * @param health 
         * @return ** void 
         */
        void setHealth(int health);

    protected:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _pos;
        sf::Clock _animationClock;
        sf::Clock _deathClock;
        ParticleSystem _particleSystem;
        sf::Color _startColor;
        sf::Color _endColor;
        int _health;
        int _maxHealth;
        sf::Sound _sound1;
        sf::SoundBuffer _soundBuf1;
        bool _deathAnimation;
        bool _deathFinish;
        float _speed;
        bool _isAlive;

    private:
};

#endif /* !ENTITY_HPP_ */
