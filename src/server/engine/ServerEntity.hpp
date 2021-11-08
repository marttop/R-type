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
        ServerEntity(const CustomRect &customRect);
        ~ServerEntity();

        void sendData();
        void update() = 0;

        void setId(int id);

        bool isAlive() const;
        int getId() const;
        CustomRect getRect() const;

        bool isColliding(const std::shared_ptr<IEntity> &other) const;

    protected:
        bool _isAlive;
        CustomRect _rect;
        std::string _type;
        int _id;
    private:
};

#endif /* !ENTITY_HPP_ */
