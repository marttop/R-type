/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IEntity.hpp"

class ServerEntity : public IEntity {
    public:
        ServerEntity(const CustomRect &customRect,
                        const std::string &type = "default",
                        int id = 0,
                        int health = 1,
                        int speed = 5);
        ~ServerEntity();

        void sendData();
        void update() = 0;

        void setId(int id);

        bool isAlive() const;
        void addLifeEntity(int lifeAdded);

        int getId() const;
        CustomRect getRect() const;

        bool isColliding(const std::shared_ptr<IEntity> &other) const;

        std::pair<double, double> getDirection() const;
        std::pair<double, double> getPosition() const;
        double getSpeed() const;

        void setPosition(double x, double y);

    protected:
        bool _isAlive;
        CustomRect _rect;
        std::string _type;
        int _id;
        std::pair<int, int> _direction;
        double _speed;
        int _health;
    private:
};

#endif /* !ENTITY_HPP_ */
