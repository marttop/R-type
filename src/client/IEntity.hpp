/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

typedef struct EntityPos {
    float x;
    float y;
};

class IEntity {
    public:

        virtual void drawEntity() = 0;

        virtual EntityPos getEntityPos() const = 0;
        virtual sf::Sprite getEntitySprite() const = 0;

        virtual void setEntityPos(EntityPos pos) = 0;
        virtual void setEntityColor(sf::Color newColor) = 0;

    protected:
    private:
};

#endif /* !IENTITY_HPP_ */
