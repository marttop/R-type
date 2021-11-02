/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "TcpConnection.hpp"

class TcpServer {
    public:
        TcpServer(boost::asio::io_service &io_service);

    private:
        void start_accept();
        void handle_accept(TcpConnection::pointer new_connection,
                        const boost::system::error_code &error);

        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::io_service &io_service_;
};

#endif /* !TCPSERVER_HPP_ */
