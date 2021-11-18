/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>
#include <math.h>

class Utils {
    public:
        Utils();
        ~Utils();

        float vectorMagnitude(const sf::Vector2f &vector) const;
        void vectorNormalize(sf::Vector2f &vector);
        float vectorSize(const sf::Vector2f &vector1, const sf::Vector2f &vector2) const;
        void rotatePointAroundCenter(sf::Vector2f &point, const sf::Vector2f &center, const float &angle_rad);
        sf::Vector2f getRandomNormalizedVector() const;
        float dotProduct(const sf::Vector2f &vector_a, const sf::Vector2f &vector_b) const;
        void posDebug(const sf::Vector2f &pos, sf::RenderWindow &window);
        bool segmentIntersectsRectangle(const sf::FloatRect &rect, const sf::Vector2f &a_p1, const sf::Vector2f &a_p2) const;

    protected:
    private:
};

#endif /* !UTILS_HPP_ */