/*
** EPITECH PROJECT, 2021
** Asio
** File description:
** connection singeltone
*/

#ifndef TCPCONNECTION_HPP
#define TCPCONNECTION_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>

class UserConnection : public std::enable_shared_from_this<UserConnection>
{
public:
    typedef std::shared_ptr<UserConnection> pointer;

    static pointer create(asio::io_context &io_context, std::vector<UserConnection::pointer> *userList, int id) {
        return pointer(new UserConnection(io_context, userList, id));
    }

    asio::ip::tcp::socket &getSocket();

    void startCommunication();

protected:
private:
    UserConnection(asio::io_context &io_context, std::vector<UserConnection::pointer> *userList, int id);

    void handleWrite(const asio::error_code &err, size_t size);
    void handleRead(const asio::error_code &error, size_t size);
    void checkCode(std::string &data);

    asio::ip::tcp::socket _socket;
    asio::streambuf _message;
    std::string _finalMessage;

    int _id;

    std::vector<UserConnection::pointer> *_userList;
};

#endif /* !TCPCONNECTION_HPP */