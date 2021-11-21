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

        /**
         * @brief Get vector magnitude
         * 
         * @param vector 
         * @return ** float 
         */
        float vectorMagnitude(const sf::Vector2f &vector) const;

        /**
         * @brief Get the Random Normalized Vector object
         * 
         * @return ** sf::Vector2f 
         */
        sf::Vector2f getRandomNormalizedVector() const;

    protected:
    private:
};

#endif /* !UTILS_HPP_ */