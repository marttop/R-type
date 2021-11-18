/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** CustomRect
*/

#include "CustomRect.hpp"

CustomRect::CustomRect(double width, double height, double x, double y)
    : tr((point){x + width, y + height}), tl((point){x, y + height}),
    br((point){x + width, y}), bl((point){x, y}), _x(x), _y(y), _width(width), _height(height)
{

}

CustomRect::~CustomRect()
{
}

void CustomRect::setPosition(double x, double y)
{
    _x = x;
    _y = y;

    tl = (point){x, y + _height};
    tr = (point){x + _width, y + _height};
    bl = (point){x, y};
    br = (point){x + _width, y};

}

std::pair<double, double> CustomRect::getPosition() const
{
    return (std::make_pair(_x, _y));
}

bool CustomRect::isColliding(const CustomRect &rect) const
{
    if (tl.x == br.x || tl.y == br.y || rect.tl.x == rect.br.x
        || rect.tl.y == rect.br.y) {
        return false;
    }
    if (tl.x >= rect.br.x || rect.tl.x >= br.x)
        return false;
    if (br.y >= rect.tl.y || rect.br.y >= tl.y)
        return false;

    return true;
}

