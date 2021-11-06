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
#include "AsioTcpServ.hpp"

class AsioTcpServ;
class UserConnection;

typedef std::shared_ptr<UserConnection> userConnectionPointer;

class UserConnection : public std::enable_shared_from_this<UserConnection>
{
public:

    static userConnectionPointer create(asio::io_context &io_context, AsioTcpServ &servRef, int id) {
        return userConnectionPointer(new UserConnection(io_context, servRef, id));
    }

    asio::ip::tcp::socket &getSocket();
    int getId() const;

    void startCommunication();


protected:
private:
    UserConnection(asio::io_context &io_context, AsioTcpServ &servRef, int id);

    void handleWrite(const asio::error_code &err, size_t size);
    void handleRead(const asio::error_code &error, size_t size);
    void checkCode(std::string &data);

    asio::ip::tcp::socket _socket;
    asio::streambuf _message;
    std::string _finalMessage;

    int _id;
    std::string _userName;
    AsioTcpServ *_servRef;
};

#endif /* !TCPCONNECTION_HPP */