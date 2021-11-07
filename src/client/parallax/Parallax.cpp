/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Parallax
*/

#include "Parallax.hpp"

Parallax::Parallax()
{
}

Parallax::~Parallax()
{
    for (auto iter : _layersVec) {
        delete iter.second.first.first;
        delete iter.second.first.second;
        delete iter.second.second.first;
        delete iter.second.second.second;
    }
}

void Parallax::create(const int &speed, const Direction &direction)
{
    _speed = speed;
    _direction = direction;

    _layerTextures[BACKGROUND].loadFromFile("assets/parallax/BKG 2/Bkg 2 Nebula.png");
    _layerTextures[FARTHEST].loadFromFile("assets/parallax/OLD/small_stars1.png");
    _layerTextures[FAR].loadFromFile("assets/parallax/OLD/small_stars2.png");
    _layerTextures[CLOSE].loadFromFile("assets/parallax/BKG 2/Bkg 2 Middle Stars NO.png");
    _layerTextures[CLOSEST].loadFromFile("assets/parallax/BKG 2/Bkg 2 Meteors.png");
    add(1.0, BACKGROUND, true);
    add(1.2, FARTHEST, true);
    add(1.4, FAR, true);
    add(1.6, CLOSE, true);
    add(1.8, CLOSEST, true);
}

void Parallax::add(const float &speed, const Layers &type, const bool &active)
{
    _layersVec.push_back(
        make_pair(
            speed,
            make_pair(
                make_pair(
                    new Layer(_layerTextures[type], sf::Vector2f{0, 0}, active),
                    new Layer(_layerTextures[type], sf::Vector2f{-float(_layerTextures[type].getSize().x), 0}, active)
                ),
                make_pair(
                    new Layer(_layerTextures[type], sf::Vector2f{0, -float(_layerTextures[type].getSize().y)}, active),
                    new Layer(_layerTextures[type], sf::Vector2f{-float(_layerTextures[type].getSize().x), -float(_layerTextures[type].getSize().y)}, active)
                )
            )
        )
    );
}

void Parallax::setDirection(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Down)
        _direction = Parallax::UP;
    if (event.key.code == sf::Keyboard::Left)
        _direction = Parallax::RIGHT;
    if (event.key.code == sf::Keyboard::Right)
        _direction = Parallax::LEFT;
    if (event.key.code == sf::Keyboard::Up)
       _direction = Parallax::DOWN;
}

void Parallax::setPosition(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter)
{
    float elapsedTime = iter.second.first.first->getElapsedTime();
    if (_direction == RIGHT) {
        iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x + iter.first * elapsedTime * _speed, iter.second.first.first->getPos().y));
        iter.second.first.second->setPos(sf::Vector2f(iter.second.first.second->getPos().x + iter.first * elapsedTime * _speed, iter.second.first.second->getPos().y));
        iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x + iter.first * elapsedTime * _speed, iter.second.second.first->getPos().y));
        iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x + iter.first * elapsedTime * _speed, iter.second.second.second->getPos().y));
    }
    if (_direction == LEFT) {
        iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x - iter.first * elapsedTime * _speed, iter.second.first.first->getPos().y));
        iter.second.first.second->setPos(sf::Vector2f(iter.second.first.second->getPos().x - iter.first * elapsedTime * _speed, iter.second.first.second->getPos().y));
        iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x - iter.first * elapsedTime * _speed, iter.second.second.first->getPos().y));
        iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x - iter.first * elapsedTime * _speed, iter.second.second.second->getPos().y));
    }
    if (_direction == UP) {
        iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x, iter.second.first.first->getPos().y - iter.first * elapsedTime * _speed));
        iter.second.first.second->setPos(sf::Vector2f(iter.second.first.second->getPos().x, iter.second.first.second->getPos().y - iter.first * elapsedTime * _speed));
        iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x, iter.second.second.first->getPos().y - iter.first * elapsedTime * _speed));
        iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.second.second->getPos().y - iter.first * elapsedTime * _speed));
    }
    if (_direction == DOWN) {
        iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x, iter.second.first.first->getPos().y + iter.first * elapsedTime * _speed));
        iter.second.first.second->setPos(sf::Vector2f(iter.second.first.second->getPos().x, iter.second.first.second->getPos().y + iter.first * elapsedTime * _speed));
        iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x, iter.second.second.first->getPos().y + iter.first * elapsedTime * _speed));
        iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.second.second->getPos().y + iter.first * elapsedTime * _speed));
    }
}

void Parallax::fillEmptySpace(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter)
{
    if (_direction == RIGHT) {
        if (iter.second.first.first->getPos().x >= iter.second.first.first->getSize().x)
            iter.second.first.first->setPos(sf::Vector2f(iter.second.first.second->getPos().x - iter.second.first.second->getSize().x, iter.second.first.first->getPos().y));
        if (iter.second.first.second->getPos().x >= iter.second.first.second->getSize().x)
            iter.second.first.second->setPos(sf::Vector2f(iter.second.first.first->getPos().x - iter.second.first.second->getSize().x, iter.second.first.second->getPos().y));
        if (iter.second.second.first->getPos().x >= iter.second.second.first->getSize().x)
            iter.second.second.first->setPos(sf::Vector2f(iter.second.second.second->getPos().x - iter.second.second.second->getSize().x, iter.second.second.first->getPos().y));
        if (iter.second.second.second->getPos().x >= iter.second.second.second->getSize().x)
            iter.second.second.second->setPos(sf::Vector2f(iter.second.second.first->getPos().x - iter.second.second.second->getSize().x, iter.second.second.second->getPos().y));
    }
    if (_direction == LEFT) {
        if (iter.second.first.first->getPos().x <= -iter.second.first.first->getSize().x)
            iter.second.first.first->setPos(sf::Vector2f(iter.second.first.second->getPos().x + iter.second.first.second->getSize().x, iter.second.first.first->getPos().y));
        if (iter.second.first.second->getPos().x <= -iter.second.first.second->getSize().x)
            iter.second.first.second->setPos(sf::Vector2f(iter.second.first.first->getPos().x + iter.second.first.second->getSize().x, iter.second.first.second->getPos().y));
        if (iter.second.second.first->getPos().x <= -iter.second.second.first->getSize().x)
            iter.second.second.first->setPos(sf::Vector2f(iter.second.second.second->getPos().x + iter.second.second.second->getSize().x, iter.second.second.first->getPos().y));
        if (iter.second.second.second->getPos().x <= -iter.second.second.second->getSize().x)
            iter.second.second.second->setPos(sf::Vector2f(iter.second.second.first->getPos().x + iter.second.second.second->getSize().x, iter.second.second.second->getPos().y));
    }
    if (_direction == UP) {
        if (iter.second.first.first->getPos().y <= -iter.second.first.first->getSize().y)
            iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x, iter.second.second.first->getPos().y + iter.second.first.first->getSize().y));
        if (iter.second.first.second->getPos().y <= -iter.second.first.second->getSize().y)
            iter.second.first.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.second.first->getPos().y + iter.second.second.second->getSize().y));
        if (iter.second.second.first->getPos().y <= -iter.second.second.first->getSize().y)
            iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x, iter.second.first.first->getPos().y + iter.second.second.first->getSize().y));
        if (iter.second.second.second->getPos().y <= -iter.second.second.second->getSize().y)
            iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.first.second->getPos().y + iter.second.second.second->getSize().y));
    }
    if (_direction == DOWN) {
        if (iter.second.first.first->getPos().y >= iter.second.first.first->getSize().y)
            iter.second.first.first->setPos(sf::Vector2f(iter.second.first.first->getPos().x, iter.second.second.first->getPos().y - iter.second.first.first->getSize().y));
        if (iter.second.first.second->getPos().y >= iter.second.first.second->getSize().y)
            iter.second.first.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.second.first->getPos().y - iter.second.second.second->getSize().y));
        if (iter.second.second.first->getPos().y >= iter.second.second.first->getSize().y)
            iter.second.second.first->setPos(sf::Vector2f(iter.second.second.first->getPos().x, iter.second.first.first->getPos().y - iter.second.second.first->getSize().y));
        if (iter.second.second.second->getPos().y >= iter.second.second.second->getSize().y)
            iter.second.second.second->setPos(sf::Vector2f(iter.second.second.second->getPos().x, iter.second.first.second->getPos().y - iter.second.second.second->getSize().y));
    }
}

void Parallax::move()
{
    for (auto iter : _layersVec) {
        if (iter.second.first.first->isActive() == true) {
            setPosition(iter);
            fillEmptySpace(iter);
            iter.second.first.first->restartClock();
        }
    }
}


void Parallax::draw(sf::RenderWindow &window)
{
    for (auto iter : _layersVec) {
        if (iter.second.first.first->isActive() == true) {
            iter.second.first.first->draw(window);
            iter.second.first.second->draw(window);
            iter.second.second.first->draw(window);
            iter.second.second.second->draw(window);
        }
    }
}