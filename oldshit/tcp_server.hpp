#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>
#include <vector>
#include <time.h>
#include <algorithm>
#include <thread>
#include "TcpConnection.hpp"

#include "IServer.hpp"




class tcp_server : public IServer
{
    public:
        tcp_server(asio::io_context &io_context);
        ~tcp_server();

        void initServ() {};
        void startServ() {};

        void writeDataToUser(int userId) {};
        void writeDataToAll() {};

        void addUser(User user) {};
        void disconnectUser(int userId) {};

    private:

        void start_accept();
        void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code &error);

        asio::ip::tcp::acceptor acceptor_;
        asio::io_context &_io_context;
};

