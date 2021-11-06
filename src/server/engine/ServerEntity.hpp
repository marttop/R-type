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
        ServerEntity();
        ~ServerEntity();

        void sendData();
        void update() = 0;
        bool isAlive() const;

        bool isColliding(const std::shared_ptr<IEntity> &other) const;
        CustomRect getRect() const;

    protected:
        bool _isAlive;
        CustomRect *_rect;
        std::string _type;
    private:
};

#endif /* !ENTITY_HPP_ */
