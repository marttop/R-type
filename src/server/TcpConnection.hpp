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

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> pointer;

    static pointer create(asio::io_context &io_context, std::vector<TcpConnection::pointer> *userList, int id) {
        return pointer(new TcpConnection(io_context, userList, id));
    }

    asio::ip::tcp::socket &getSocket();

    void startCommunication();

protected:
private:
    TcpConnection(asio::io_context &io_context, std::vector<TcpConnection::pointer> *userList, int id);

    void handleWrite(const asio::error_code &err, size_t size);
    void handleRead(const asio::error_code &error, size_t size);
    void checkCode(std::string &data);

    asio::ip::tcp::socket _socket;
    asio::streambuf _message;
    std::string _finalMessage;

    int _id;

    std::vector<TcpConnection::pointer> *_userList;
};

#endif /* !TCPCONNECTION_HPP */