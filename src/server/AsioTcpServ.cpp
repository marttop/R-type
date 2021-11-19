/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** asio server
*/

#include "AsioTcpServ.hpp"

AsioTcpServ::AsioTcpServ(asio::io_context &io_context, const int port, bool debug)
    : _io_context(io_context), _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    _debug = debug;
    start_accept();
}

AsioTcpServ::~AsioTcpServ()
{
}

int AsioTcpServ::addRoom()
{
    static int id = 0;
    static int portSeed = 8888;
    portSeed += 150;
    id++;

    std::shared_ptr<ServerRoom> room(new ServerRoom(_io_context, id, portSeed, _debug));
    _roomList.push_back(room);

    return (id);
}

void AsioTcpServ::start_accept()
{
    static int id = 0;
    id++;

    userConnectionPointer new_connection = UserConnection::create(_io_context, *this, id, _debug);

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
    if (_debug) {
        std::cout << "client accepted" << std::endl;
        std::cout << "client infos:" << std::endl;
        std::cout << "ip ---> " << new_connection->getSocket().remote_endpoint().address().to_string() << std::endl;
        std::cout << "port ---> " << new_connection->getSocket().remote_endpoint().port() << std::endl << std::endl;
    }
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

int AsioTcpServ::deleteRoomById(int id)
{
    int tmp = -1, i = 0;
    for (auto itr : _roomList) {
        if (itr->getId() == id) {
            if (itr->getNbUsers() == 0) {
                tmp = i;
                break;
            }
        }
        i++;
    }
    if (tmp != -1) {
        _roomList.erase(_roomList.begin() + tmp);
        return (1);
    }
    return (0);
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
