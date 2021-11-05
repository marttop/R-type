/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** User
*/

#ifndef USER_HPP_
#define USER_HPP_

#include <string>
#include <asio.hpp>
// #include <TcpConnection.cpp>

class User {
    public:
        User(short port);
        ~User();

        short getPort() const;
        std::string getIp() const;

    protected:
    private:
        
};

#endif /* !USER_HPP_ */
