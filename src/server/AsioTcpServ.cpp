/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** asio server
*/

#include "AsioTcpServ.hpp"

AsioTcpServ::AsioTcpServ(asio::io_context &io_context, const int port)
    : _io_context(io_context), _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    start_accept();
}

AsioTcpServ::~AsioTcpServ()
{
}

int AsioTcpServ::addRoom()
{
    static int id = 0;
    id++;

    std::shared_ptr<ServerRoom> room(new ServerRoom(_io_context, id));
    _roomList.push_back(room);

    return (id);
}

void AsioTcpServ::start_accept()
{
    static int id = 0;
    id++;

    userConnectionPointer new_connection = UserConnection::create(_io_context, *this, id);

    _acceptor.async_accept(new_connection->getSocket(),
                            std::bind(&AsioTcpServ::handle_connexion, this, new_connection,
                                    std::placeholders::_1));
}

void AsioTcpServ::shell_send() const
{
    std::string message;
    while(true) {
        std::cin >> message;

    }
}

void AsioTcpServ::handle_connexion(userConnectionPointer new_connection,
                                    const asio::error_code &error)
{
    std::cout << "client accepted" << std::endl;
    if (!error) {
        new_connection->startCommunication();
        _userList.push_back(new_connection);
    }

    start_accept();
}

std::vector<userConnectionPointer> &AsioTcpServ::getUserList()
{
    return (_userList);
}

std::vector<std::shared_ptr<ServerRoom>> &AsioTcpServ::getRoomList()
{
    return (_roomList);
}

void AsioTcpServ::deleteRoomById(int id)
{
    int tmp = -1, i = 0;
    for (auto itr : _roomList) {
        if (itr->getId() == id) {
            tmp = i;
        }
        i++;
    }
    if (tmp != -1) {
        _roomList.erase(_roomList.begin() + tmp);
    } else {
        _roomList.clear();
    }
}

std::shared_ptr<ServerRoom> AsioTcpServ::getRoomById(int id)
{
    for (auto itr : _roomList) {
        if (id == itr->getId()) {
            return (itr);
        }
    }
    return (nullptr);
}
