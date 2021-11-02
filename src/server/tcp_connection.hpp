/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** tcp_connection
*/

#ifndef TCP_CONNECTION_HPP_
#define TCP_CONNECTION_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <time.h>
#include <algorithm>
#include <thread>

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
    public:
        typedef boost::shared_ptr<tcp_connection> pointer;

        static pointer create(boost::asio::io_service& io_service);

        boost::asio::ip::tcp::socket& socket();

        void start();

    private:
        tcp_connection(boost::asio::io_service& io_service);

        void handle_write(const boost::system::error_code& code,
                        size_t byte_read);

        boost::asio::ip::tcp::socket socket_;
        std::string message_;
};

#endif /* !TCP_CONNECTION_HPP_ */
