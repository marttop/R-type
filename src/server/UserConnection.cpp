/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Babel singelton
*/

#include "UserConnection.hpp"

UserConnection::UserConnection(asio::io_context &io_context, AsioTcpServ &servRef, int id)
    : _socket(io_context), _servRef(&servRef), _id(id)
{
    _cmd.emplace(210, &UserConnection::cmdConnection);
    _cmd.emplace(220, &UserConnection::cmdJoinRoom);
    _cmd.emplace(300, &UserConnection::cmdRoomCreate);
}

asio::ip::tcp::socket &UserConnection::getSocket()
{
    return _socket;
}

int UserConnection::getId() const
{
    return (_id);
}

void UserConnection::startCommunication()
{

    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();

    for (auto user : *_userList) {
        if (user->getId() != _id) {
            user->getSocket().write_some(asio::buffer("150 " + std::to_string(_id) + "\n"));
        }
    }

    asio::async_write(_socket, asio::buffer("Welcomeeeeeeeeeeeeeee !\n"),
                        std::bind(&UserConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}

void UserConnection::handleWrite(const asio::error_code &error, size_t size)
{
    asio::async_read_until(_socket, _message, "\n",
                            std::bind(&UserConnection::handleRead, shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));

}

void UserConnection::checkCode(std::string &data)
{
    int len = data.length();
    char local_data[len + 1];
    char *token = NULL;
    std::strcpy(local_data, data.c_str());
    token = std::strtok(local_data, " \n");
    std::cout << data << std::endl;
    while (token != NULL) {
        token = std::strtok(NULL, " \n");
        std::cout << token << std::endl;
    }
}

void UserConnection::sendError(const std::string &msg)
{
    std::stringstream ss;
    ss << "500 ";
    ss << msg;
    ss << "\n";
    _socket.write_some(asio::buffer(ss.str()));
}

void UserConnection::broadcastTCP(const std::string &msg) const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();
    for (auto user : *_userList) {
        user->getSocket().write_some(asio::buffer(msg));
    }
}

void UserConnection::broadcastTCPNotUser(const std::string &msg) const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();
    for (auto user : *_userList) {
        if (user->getId() != _id) {
            user->getSocket().write_some(asio::buffer(msg));
        }
    }
}

void UserConnection::checkDisconnection() const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();
    int tmp = -1, i = 0;
    for (auto user : *_userList) {
        if (user->getId() != _id) {
            user->getSocket().write_some(asio::buffer("250 " + std::to_string(_id) + "\n"));
        }
        else {
            tmp = i;
        }
        i++;
    }
    if (tmp != -1) {
        _userList->erase(_userList->begin() + tmp);
    } else {
        _userList->clear();
    }
}

void UserConnection::handleRead(const asio::error_code &error, size_t size)
{
    std::string sendMessage = "";
    std::istream is(&_message);
    std::string line;
    std::getline(is, line);

    if (line != "") {
        std::cout << "tcp line: " + line << std::endl;
        std::vector<std::string> arg = SEPParsor::parseCommands(line);
        if (_cmd.count(std::atoi(arg[0].c_str()))) {
            UserConnection::factoryF func = _cmd[std::atoi(arg[0].c_str())];
            (this->*func)(arg);
        }
        else {
            sendError("Unknown command");
        }
    } else {
        checkDisconnection();
        return;
    }

    handleWrite(error, size);
}

///////////////////////////////////////////////////////////////
//-----------------------CMD_RESPONSES-----------------------//
///////////////////////////////////////////////////////////////

void UserConnection::cmdConnection(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        _userName = arg[1];
        std::stringstream ss;
        ss << "220";

        std::vector<std::shared_ptr<ServerRoom>> roomList = _servRef->getRoomList();

        for (auto itr : roomList) {
            ss << " ";
            ss << itr->getId();
            ss << " ";
            ss << itr->getNbUsers();
        }

        ss << "\n";
        _socket.send(asio::buffer(ss.str()));

    } else {
        sendError("Missing arg in command");
    }
}

void UserConnection::cmdRoomCreate(const std::vector<std::string> &arg)
{
    if (arg.size() >= 1) {
        int id = _servRef->addRoom();
        std::string response = "310 " + std::to_string(id) + "\n";
        broadcastTCP(response);
    } else {
        sendError("Weird error");
    }
}

void UserConnection::cmdJoinRoom(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        std::stringstream ss;
        std::shared_ptr<ServerRoom> room = _servRef->getRoomById(std::atoi(arg[1].c_str()));
        if (room != nullptr) {
            room->addUser(_id, _userName);
            ss << "230 ";
            ss << room->getPlayersName();
            ss << "\n";
            _socket.send(asio::buffer(ss.str()));
            broadcastTCPNotUser("280 " + std::to_string(room->getId()) + "\n");

        } else {
            sendError("'id' of room does not exist");
        }
    } else {
        sendError("Missing arg in command");
    }
}

void UserConnection::cmdQuitRoom(const std::vector<std::string> &arg)
{

}
