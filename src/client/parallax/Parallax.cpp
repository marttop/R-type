/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Parallax
*/

#include "Parallax.hpp"

Parallax::Parallax()
{
    _layerTextures[NEBULA_AQUA_PINK].loadFromFile("assets/nebula_aqua_pink.png");
    _layerTextures[NEBULA_BLUE].loadFromFile("assets/nebula_blue.png");
    _layerTextures[NEBULA_RED].loadFromFile("assets/nebula_red.png");
    _layerTextures[SMALL_STARS1].loadFromFile("assets/small_stars1.png");
    _layerTextures[SMALL_STARS2].loadFromFile("assets/small_stars2.png");
    _layerTextures[BIG_STARS1].loadFromFile("assets/big_stars1.png");
    _layerTextures[BIG_STARS2].loadFromFile("assets/big_stars2.png");
    add(1.0, NEBULA_AQUA_PINK, false);
    add(1.0, NEBULA_BLUE, true);
    add(1.0, NEBULA_RED, false);
    add(2.0, BIG_STARS1, true);
    add(2.0, SMALL_STARS1, true);
    add(20.0, BIG_STARS2, true);
    add(20.0, SMALL_STARS2, true);

    _multiplier = 35;
}

Parallax::~Parallax()
{
}

void Parallax::add(const float &speed, const Layers &type, const bool &active)
{
    _layersVec.push_back(
        make_pair(
            speed,
            make_pair(
                Layer(_layerTextures[type], sf::Vector2f{0, 0}, active),
                Layer(_layerTextures[type], sf::Vector2f{0, -float(_layerTextures[type].getSize().y)}, active)
            )
        )
    );
}

void Parallax::move()
{
    for (auto iter : _layersVec) {
        if (iter.second.first.isActive() == true) {
            iter.second.first.setPos(sf::Vector2f(iter.second.first.getPos().x, iter.second.first.getPos().y + (iter.first * iter.second.first.getElapsedTime() * _multiplier)));
            iter.second.second.setPos(sf::Vector2f(iter.second.second.getPos().x, iter.second.second.getPos().y + (iter.first * iter.second.first.getElapsedTime() * _multiplier)));
            if (iter.second.first.getPos().y >= iter.second.first.getSize().y)
                iter.second.first.setPos(sf::Vector2f(iter.second.first.getPos().x, iter.second.first.getPos().y - iter.second.first.getSize().y * 2));
            if (iter.second.second.getPos().y >= iter.second.second.getSize().y)
                iter.second.second.setPos(sf::Vector2f(iter.second.second.getPos().x, iter.second.second.getPos().y - iter.second.second.getSize().y * 2));
            iter.second.first.restartClock();
        }
    }
}


void Parallax::draw(sf::RenderWindow &window)
{
    for (auto iter : _layersVec) {
        if (iter.second.first.isActive() == true) {
            iter.second.first.draw(window);
            iter.second.second.draw(window);
        }
    }
}