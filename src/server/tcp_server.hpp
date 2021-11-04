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
#include "tcp_connection.hpp"




class tcp_server {
    public:
        tcp_server(boost::asio::io_service &io_service);

    private:
        void start_accept();
        void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error);

        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::io_service &io_service_;
};
