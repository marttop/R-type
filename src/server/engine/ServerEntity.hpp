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
                        const std::string &id = "0",
                        int speed = 5,
                        int health = 1);
        ~ServerEntity();

        void sendData();
        void update() = 0;

        void setId(const std::string id);

        bool isAlive() const;
        void addLifeEntity(int lifeAdded);

        std::string getId() const;
        CustomRect getRect() const;

        bool isColliding(const std::shared_ptr<IEntity> &other) const;

        std::pair<double, double> getDirection() const;
        std::pair<double, double> getPosition() const;
        std::string getType() const;
        double getSpeed() const;

        void setPosition(double x, double y);
        int getHp() const;

    protected:
        bool _isAlive;
        CustomRect _rect;
        std::string _type;
        std::string _id;
        std::pair<int, int> _direction;
        double _speed;
        int _health;
    private:
};

#endif /* !ENTITY_HPP_ */
