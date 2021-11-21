/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Particles
*/

#ifndef PARTICLES_HPP_
#define PARTICLES_HPP_

#include "Utils.hpp"

class Particle
{
    public:
        Particle(const sf::Color &startColor, const sf::Color &endColor, const int &life, const sf::Vector2f &direction, const sf::Vector2f &randomDirection);
        ~Particle();

        /**
         * @brief Set the Direction object
         * 
         * @param direction 
         * @return ** void 
         */
        void setDirection(const sf::Vector2f &direction);

        /**
         * @brief Set the Random Direction object
         * 
         * @param randomDirection 
         * @return ** void 
         */
        void setRandomDirection(const sf::Vector2f &randomDirection);

        /**
         * @brief Set the Position object
         * 
         * @param position 
         * @return ** void 
         */
        void setPosition(const sf::Vector2f &position);

        /**
         * @brief Set the Color object
         * 
         * @param color 
         * @return ** void 
         */
        void setColor(const sf::Color &color);

        /**
         * @brief Set the Time Step object
         * 
         * @param timeStep 
         * @return ** void 
         */
        void setTimeStep(const float &timeStep);

        /**
         * @brief Get the Time Step object
         * 
         * @return ** float 
         */
        float getTimeStep() const;

        /**
         * @brief Get the Life object
         * 
         * @return ** int 
         */
        int getLife() const;

        /**
         * @brief Get the Start Color object
         * 
         * @return ** sf::Color 
         */
        sf::Color getStartColor() const;

        /**
         * @brief Get the End Color object
         * 
         * @return ** sf::Color 
         */
        sf::Color getEndColor() const;

        /**
         * @brief Get the Position object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getPosition() const;

        /**
         * @brief Get the Direction object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getDirection() const;

        /**
         * @brief Set the Colors object
         * 
         * @param startColor 
         * @param endColor 
         * @return ** void 
         */
        void setColors(const sf::Color &startColor, const sf::Color &endColor);

        /**
         * @brief Get the Random Direction object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getRandomDirection() const;

        /**
         * @brief Get the Particle object
         * 
         * @return ** sf::VertexArray 
         */
        sf::VertexArray getParticle() const;

    protected:
    private:
        sf::Color _startColor;
        sf::Color _endColor;
        sf::VertexArray _part;
        sf::Vector2f _direction;
        sf::Vector2f _randomDirection;
        int _life;
        float _timeStep;
        bool _dead;
};

class ParticleSystem
{
    public:
        ParticleSystem();
        ~ParticleSystem();

        void update(const sf::Vector2f &offset, const sf::Vector2f &direction, const sf::Vector2f &position, const sf::Color &startColor, const sf::Color &endColor, const int &life, const int &isRand);
        void drawParticles(sf::RenderWindow &window);

    protected:
    private:
        sf::Color rgbInterpolation(const sf::Color &startColor, const float &timeStep, const sf::Color &endColor) const;
        Particle *createParticle(const sf::Color &startColor, const sf::Color &endColor, const sf::Vector2f &offset, const sf::Vector2f &direction, const sf::Vector2f &randomDirection, const sf::Vector2f &position, const int &life);

        std::vector<Particle *> _particles;
        Utils _utils;
};

#endif /* !PARTICULES_HPP_ */