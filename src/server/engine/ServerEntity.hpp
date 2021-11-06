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
        ServerEntity() = default;

        void sendData();
        void update() = 0;
        bool isAlive() const;

        void checkCollision();

    protected:
        bool _isAlive;
        std::string _type;
    private:
};

#endif /* !ENTITY_HPP_ */
