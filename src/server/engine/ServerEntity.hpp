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

        /**
         * @brief Not used function
         * 
         */
        void sendData();

        void update() = 0;

        void setId(const std::string id);

        bool isAlive() const;
        void setAlive(bool life);
        void addLifeEntity(int lifeAdded);

        std::string getId() const;
        CustomRect getRect() const;

        bool isColliding(const std::shared_ptr<IEntity> &other) const;

        void setDirection(double x, double y);
        std::pair<double, double> getDirection() const;
        std::pair<double, double> getPosition() const;
        std::string getType() const;
        double getSpeed() const;
        int getMaxHp() const;

        void setPosition(double x, double y);
        int getHp() const;

        std::vector<std::shared_ptr<IEntity>> getAmmos() const;
        void clearAmmos();

    protected:
        bool _isAlive;
        CustomRect _rect;
        std::string _type;
        std::string _id;
        std::pair<double, double> _direction;
        std::vector<std::shared_ptr<IEntity>> _ammos;
        double _speed;
        int _health;
        int _maxHealth;
    private:
};

#endif /* !ENTITY_HPP_ */
