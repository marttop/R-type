/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** serveur tcp asio lib
*/

#ifndef ASIOTCPSERV_HPP
#define ASIOTCPSERV_HPP

#include "UserConnection.hpp"
#include <vector>
#include "ServerRoom.hpp"

class UserConnection;
class ServerRoom;
typedef std::shared_ptr<UserConnection> userConnectionPointer;

class AsioTcpServ
{
public:
    AsioTcpServ(asio::io_context& io_context, const int port, bool debug = false);
    ~AsioTcpServ();

    /**
     * @brief Starts the server's TCP communication.
     * Waits for new clients.
     */
    void start_accept();

    /**
     * @brief Add a new room in the room list.
     *
     * @return the id of the new room.
     */
    int addRoom();

    //Not const because need to modify the getted vector.

    /**
     * @brief Get the TCP User's list.
     *
     * @return list of users.
     */
    std::vector<userConnectionPointer> &getUserList();

    /**
     * @brief Get the room's list.
     *
     * @return list of rooms.
     */
    std::vector<std::shared_ptr<ServerRoom>> &getRoomList();

    /**
     * @brief Get the Room By Id object
     *
     * @param id of the room.
     * @return std::shared_ptr<ServerRoom> list.
     */
    std::shared_ptr<ServerRoom> getRoomById(int id);

    /**
     * @brief Removes the room from the list by id.
     *
     * @param id of the room to be removed.
     * @return id of the next room.
     */
    int deleteRoomById(int id);

protected:
private:
    void handle_connexion(userConnectionPointer new_connection, const asio::error_code& error);

    bool _debug;
    asio::io_context &_io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<userConnectionPointer> _userList;
    std::vector<std::shared_ptr<ServerRoom>> _roomList;
};

#endif /* !ASIOTCPSERV_HPP */