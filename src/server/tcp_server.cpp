/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** tcp_server
*/

#include "tcp_server.hpp"

void enable_multi_threading(size_t nb, boost::asio::io_service &io_service) {
    //TODO implement multi-threading (Task 04)
}

tcp_server::tcp_server(boost::asio::io_service &io_service)
        : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)),
          io_service_(io_service) {
    start_accept();
}

void tcp_server::start_accept() {
    tcp_connection::pointer new_connection =
            tcp_connection::create(io_service_);

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error) {
    if (!error) {
        new_connection->start();
        std::cout << "New connection" << std::endl;
        //TODO uncomment this line (Task 05)
        //thread_attack(io_service_);
        start_accept();
    }
}