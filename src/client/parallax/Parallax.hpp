/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Parallax
*/


#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <vector>

#include "Layer.hpp"

using namespace std;

class Parallax {
    public:
        enum Layers {
            BACKGROUND,
            FARTHEST,
            FAR,
            CLOSE,
            CLOSEST,
        };

        enum Direction {
            LEFT,
            RIGHT,
            UP,
            DOWN
        };

        Parallax();
        ~Parallax();

        void create(const int &speed, const Direction &direction);
        void move();
        void draw(sf::RenderWindow &window);
        void setDirection(const sf::Event &event);

    protected:
    private:
        void fillEmptySpace(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter);
        void setPosition(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter);
        void add(const float &speed, const Layers &type, const bool &active);

        vector<pair<float, pair<pair<Layer *, Layer *>, pair<Layer *, Layer *>>>> _layersVec;
        sf::Texture _layerTextures[7];
        Direction _direction;
        int _speed;

};

#endif /* !PARALLAX_HPP_ */