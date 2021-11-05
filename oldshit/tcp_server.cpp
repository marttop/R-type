/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** tcp_server
*/

#include "tcp_server.hpp"

void enable_multi_threading(size_t nb, asio::io_service &io_service) {
    //TODO implement multi-threading (Task 04)
}

tcp_server::tcp_server(asio::io_context &io_context)
        : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4242)),
          _io_context(io_context) {
    start_accept();
}

tcp_server::~tcp_server()
{
}

void tcp_server::start_accept() {
    TcpConnection::pointer new_connection =
            TcpConnection::create(_io_context);

    acceptor_.async_accept(new_connection->_socket(),
                           std::bind(&tcp_server::handle_accept, this, new_connection,
                                       asio::placeholders::error));
}

void tcp_server::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code &error) {
    if (!error) {
        new_connection->start();
        std::cout << "New connection" << std::endl;
        //TODO uncomment this line (Task 05)
        //thread_attack(_io_context);
        start_accept();
    }
}