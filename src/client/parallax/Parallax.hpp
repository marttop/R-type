/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Parallax
*/


#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include "Layer.hpp"
#include <vector>

using namespace std;

class Parallax {
    public:
        enum Layers {
            NEBULA_AQUA_PINK,
            NEBULA_RED,
            NEBULA_BLUE,
            SMALL_STARS1,
            SMALL_STARS2,
            BIG_STARS1,
            BIG_STARS2
        };

        Parallax();
        ~Parallax();

        void move();
        void draw(sf::RenderWindow &window);
        void add(const float &speed, const Layers &type, const bool &active);

    protected:
    private:
        vector<pair<float, pair<Layer, Layer>>> _layersVec;
        sf::Texture _layerTextures[7];
        int _multiplier;

};

#endif /* !PARALLAX_HPP_ */