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
#include "AssetManager.hpp"

using namespace std;

class Parallax {
    public:
        enum Layers {
            BACKGROUND,
            PLANET,
            FARTHEST,
            FARE,
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

        void create(const int &speed);
        void update();
        void draw(sf::RenderWindow &window) const;
        void event(const sf::Event &event);
        void setDirection(const std::vector<bool> &direction);

    protected:
    private:
        void fillEmptySpace(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter);
        void setPosition(struct std::pair<float, std::pair<std::pair<Layer *, Layer *>, std::pair<Layer *, Layer *>>> iter);
        void add(const float &speed, const Layers &type, const bool &active);

        vector<pair<float, pair<pair<Layer *, Layer *>, pair<Layer *, Layer *>>>> _layersVec;
        sf::Texture _layerTextures[6];
        bool _direction[4];
        int _speed;

};

#endif /* !PARALLAX_HPP_ */