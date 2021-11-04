/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <string>

class IEntity {
    public:
        IEntity() = default;
        virtual ~IEntity() = default;
        virtual void update() = 0;
        virtual void sendData() = 0;

    protected:
    private:
};

#endif /* !IENTITY_HPP_ */
