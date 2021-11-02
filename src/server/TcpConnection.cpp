/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"

std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
}

boost::shared_ptr<TcpConnection> TcpConnection::create(boost::asio::io_service &io_service) {
    return pointer(new TcpConnection(io_service));
}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return socket_;
}

void TcpConnection::start() {
    message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&TcpConnection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

TcpConnection::TcpConnection(boost::asio::io_service &io_service) : socket_(io_service)  {}

void TcpConnection::handle_write(const boost::system::error_code &code, size_t byte_read) {}