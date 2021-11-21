/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Utils
*/

#include "Utils.hpp"

Utils::Utils()
{
}

Utils::~Utils()
{
}

float Utils::vectorMagnitude(const sf::Vector2f &vector) const
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
}

sf::Vector2f Utils::getRandomNormalizedVector() const
{
    float randX = (-1.0f + float(rand() % 200 / 100.0f));
    float randY = (-1.0f + float(rand() % 200 / 100.0f));

    return (sf::Vector2f(randX, randY));
}