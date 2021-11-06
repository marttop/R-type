/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** CustomRect
*/

#ifndef CUSTOMRECT_HPP_
#define CUSTOMRECT_HPP_

struct point {
    double x, y;
};

class CustomRect {
    public:
        CustomRect(double width, double height, double x = 0, double y = 0);
        ~CustomRect();

        void setPosition(double x, double y);
        bool isColliding(const CustomRect &rect) const;

        point tr;
        point tl;
        point br;
        point bl;
    protected:
    private:
        double _x;
        double _y;
        double _width;
        double _height;
};

#endif /* !CUSTOMRECT_HPP_ */
