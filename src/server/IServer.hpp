/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include "User.hpp"

class IServer {
    public:

        virtual ~IServer(){};
        virtual void initServ() = 0;
        virtual void startServ() = 0;

        virtual void writeDataToUser(int userId) = 0;
        virtual void writeDataToAll() = 0;

        virtual void addUser(User user) = 0;
        virtual void disconnectUser(int userId) = 0;

    protected:
    private:
};

#endif /* !ISERVER_HPP_ */
