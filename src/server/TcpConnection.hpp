/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** TcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include "../common/netCommon.hpp"

class TcpConnection
        : public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& socket();

    void start();

private:
    TcpConnection(boost::asio::io_service& io_service);

    void handle_write(const boost::system::error_code& code,
                      size_t byte_read);

    boost::asio::ip::tcp::socket socket_;
    std::string message_;
};

#endif /* !TCPCONNECTION_HPP_ */
