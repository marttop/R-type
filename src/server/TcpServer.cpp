/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

void enable_multi_threading(size_t nb, boost::asio::io_service &io_service) {
    //TODO implement multi-threading (Task 04)
}

TcpServer::TcpServer(boost::asio::io_service &io_service)
        : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)),
          io_service_(io_service) {
    start_accept();
}

void TcpServer::start_accept() {
    TcpConnection::pointer new_connection =
            TcpConnection::create(io_service_);

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&TcpServer::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code &error) {
    if (!error) {
        new_connection->start();
        std::cout << "New connection" << std::endl;
        //TODO uncomment this line (Task 05)
        //thread_attack(io_service_);
        start_accept();
    }
}