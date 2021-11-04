/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** tcp_connection
*/

#include "tcp_connection.hpp"

std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
}

boost::shared_ptr<tcp_connection> tcp_connection::create(boost::asio::io_service &io_service) {
    return pointer(new tcp_connection(io_service));
}

boost::asio::ip::tcp::socket &tcp_connection::socket() {
    return socket_;
}

void tcp_connection::start() {
    message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

tcp_connection::tcp_connection(boost::asio::io_service &io_service) : socket_(io_service)  {}

void tcp_connection::handle_write(const boost::system::error_code &code, size_t byte_read) {}