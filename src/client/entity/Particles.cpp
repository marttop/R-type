/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Particle
*/

#include "Particles.hpp"

Particle::Particle(const sf::Color &startColor, const sf::Color &endColor, const int &life, const sf::Vector2f &direction, const sf::Vector2f &randomDirection)
{
    _part = sf::VertexArray(sf::Points, 1);
    _life = life;
    _startColor = startColor;
    _endColor = endColor;
    _timeStep = 0.0f;
    _dead = false;
    _direction = direction;
    _randomDirection = randomDirection;
}

Particle::~Particle()
{
}

void Particle::setDirection(const sf::Vector2f &direction)
{
    _direction = direction;
}

void Particle::setRandomDirection(const sf::Vector2f &randomDirection)
{
    _randomDirection = randomDirection;
}

void Particle::setPosition(const sf::Vector2f &position)
{
    _part[0].position = position;
}

void Particle::setColor(const sf::Color &color)
{
    _part[0].color = color;
}

void Particle::setTimeStep(const float &timeStep)
{
    _timeStep = timeStep;
}

float Particle::getTimeStep() const
{
    return (_timeStep);
}

int Particle::getLife() const
{
    return (_life);
}

sf::Color Particle::getStartColor() const
{
    return (_startColor);
}

sf::Color Particle::getEndColor() const
{
    return (_endColor);
}

sf::Vector2f Particle::getPosition() const
{
    return (_part[0].position);
}

sf::Vector2f Particle::getDirection() const
{
    return (_direction);
}

void Particle::setColors(const sf::Color &startColor, const sf::Color &endColor)
{
    _startColor = startColor;
    _endColor = endColor;
}

sf::Vector2f Particle::getRandomDirection() const
{
    return (_randomDirection);
}

sf::VertexArray Particle::getParticle() const
{
    return (_part);
}

/* PARTICLE SYSTEM */

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
    for (auto it : _particles)
        delete it;
}

sf::Color ParticleSystem::rgbInterpolation(const sf::Color &startColor, const float &timeStep, const sf::Color &endColor) const
{
	sf::Color finalColor;

	finalColor.r = startColor.r + (endColor.r - startColor.r) * timeStep;
	finalColor.g = startColor.g + (endColor.g - startColor.g) * timeStep;
	finalColor.b = startColor.b + (endColor.b - startColor.b) * timeStep;
	finalColor.a = startColor.a + (endColor.a - startColor.a) * timeStep;

	return (finalColor);
}

Particle *ParticleSystem::createParticle(const sf::Color &startColor, const sf::Color &endColor, const sf::Vector2f &offset, const sf::Vector2f &direction, const sf::Vector2f &randomDirection, const sf::Vector2f &position, const int &life)
{
    Particle *particle = new Particle(startColor, endColor, life, direction, randomDirection);

    sf::Vector2f posCpy = position;
    sf::Vector2f dirCpy = direction;
    posCpy.x += offset.x;
    posCpy.y += offset.y;
    float angleDirection = atan2((dirCpy.y - posCpy.y), (dirCpy.x - posCpy.x));
    dirCpy = sf::Vector2f(cos(angleDirection), sin(angleDirection));
    float magnitude = _utils.vectorMagnitude(dirCpy);
    particle->setDirection(sf::Vector2f(dirCpy.x / magnitude, dirCpy.y / magnitude));
    particle->setPosition(posCpy);
    particle->setColor(rgbInterpolation(startColor, particle->getTimeStep(), endColor));

    return (particle);
}

void ParticleSystem::update(const sf::Vector2f &offset, const sf::Vector2f &direction, const sf::Vector2f &position, const sf::Color &startColor, const sf::Color &endColor, const int &life, const int &isRand)
{
    int number = _utils.vectorMagnitude(sf::Vector2f(direction.x, direction.y));
    if (number == 0) number = 1;
    else if (number > 3) number = 3;

    int speed = _utils.vectorMagnitude(sf::Vector2f(direction.x, direction.y)) / 2;
    if (speed == 0) speed = 1;
    else if (speed > 5) speed = 5;

    int tmpLife = life;
    for (int i = 0, value = 10; i != number; i++) {
        if (isRand == 1) tmpLife = rand() % life;
        _particles.push_back(createParticle(startColor, endColor, sf::Vector2f{static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.x))), static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.y)))}, direction, _utils.getRandomNormalizedVector(), position, tmpLife));
        if (isRand == 1) tmpLife = rand() % life;
        _particles.push_back(createParticle(startColor, endColor, sf::Vector2f{-(static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.x)))), -(static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.y))))}, direction, _utils.getRandomNormalizedVector(), position, tmpLife));
        if (isRand == 1) tmpLife = rand() % life;
        _particles.push_back(createParticle(startColor, endColor, sf::Vector2f{static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.x))), -(static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.y))))}, direction, _utils.getRandomNormalizedVector(), position, tmpLife));
        if (isRand == 1) tmpLife = rand() % life;
        _particles.push_back(createParticle(startColor, endColor, sf::Vector2f{-(static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.x)))), static_cast<float>(rand() % static_cast<int>(((value - value / 3) + offset.y)))}, direction, _utils.getRandomNormalizedVector(), position, tmpLife));
    }
    for (size_t i = 0; i < _particles.size(); i++) {
        _particles[i]->setTimeStep(_particles[i]->getTimeStep() + (1.0f / _particles[i]->getLife()));
        sf::Color resColor = rgbInterpolation(_particles[i]->getStartColor(), _particles[i]->getTimeStep(), _particles[i]->getEndColor());
        _particles[i]->setColor(resColor);
        _particles[i]->setPosition(
            sf::Vector2f{_particles[i]->getPosition().x + (_particles[i]->getDirection().x * speed),
            _particles[i]->getPosition().y + (_particles[i]->getDirection().y * (_particles[i]->getRandomDirection().y * speed))}
        );
        if (_particles[i]->getTimeStep() > 1.0f) {
            delete _particles[i];
            _particles.erase(_particles.begin() + i);
        }
    }
}

void ParticleSystem::drawParticles(sf::RenderWindow &window)
{
    for (size_t i = 0; i < _particles.size(); i++)
        window.draw(_particles[i]->getParticle());
}