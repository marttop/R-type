/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** serveur tcp asio lib
*/

#ifndef ASIOTCPSERV_HPP
#define ASIOTCPSERV_HPP

#include "UserConnection.hpp"
#include "IServer.hpp"
#include <vector>
#include "ServerRoom.hpp"

class UserConnection;
class ServerRoom;
typedef std::shared_ptr<UserConnection> userConnectionPointer;

class AsioTcpServ : public IServer
{
public:
    AsioTcpServ(asio::io_context& io_context, const int port);
    ~AsioTcpServ();

    void initServ() {};
    void startServ() {};
    void writeDataToUser(int userId) {};
    void writeDataToAll() {};
    void disconnectUser(int userId) {};

    void start_accept();
    void shell_send() const;
    int addRoom();

    //Not const because need to modify the getted vector.
    std::vector<userConnectionPointer> &getUserList();
    std::vector<std::shared_ptr<ServerRoom>> &getRoomList();

protected:
private:
    void handle_connexion(userConnectionPointer new_connection, const asio::error_code& error);

    asio::io_context &_io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<userConnectionPointer> _userList;
    std::vector<std::shared_ptr<ServerRoom>> _roomList;
};

#endif /* !ASIOTCPSERV_HPP */