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

        void setDirection(const sf::Vector2f &direction);
        void setRandomDirection(const sf::Vector2f &randomDirection);
        void setPosition(const sf::Vector2f &position);
        void setColor(const sf::Color &color);
        void setTimeStep(const float &timeStep);
        float getTimeStep() const;
        int getLife() const;
        sf::Color getStartColor() const;
        sf::Color getEndColor() const;
        sf::Vector2f getPosition() const;
        sf::Vector2f getDirection() const;
        void setColors(const sf::Color &startColor, const sf::Color &endColor);
        sf::Vector2f getRandomDirection() const;
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