/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** serveur tcp asio lib
*/

#ifndef ASIOTCPSERV_HPP
#define ASIOTCPSERV_HPP

#include "TcpConnection.hpp"
#include "IServer.hpp"

class AsioTcpServ
{
public:
    AsioTcpServ(asio::io_context& io_context, const int port);
    ~AsioTcpServ();

    void initServ() {};
    void startServ() {};
    void writeDataToUser(int userId) {};
    void writeDataToAll() {};
    void addUser(User user) {};
    void disconnectUser(int userId) {};

    void    start_accept();

protected:
private:
    void    handle_connexion(TcpConnection::pointer new_connection, const asio::error_code& error);

    asio::io_context& _io_context;
    asio::ip::tcp::acceptor _acceptor;
};

#endif /* !ASIOTCPSERV_HPP */
