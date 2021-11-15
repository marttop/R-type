/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Babel singelton
*/

#include "UserConnection.hpp"

UserConnection::UserConnection(asio::io_context &io_context, AsioTcpServ &servRef, int id, bool debug)
    : _socket(io_context), _servRef(&servRef), _id(id), _isUDPOn(false), _roomId(-1)
{
    _debug = debug;
    _cmd.emplace(108, &UserConnection::cmdActions);
    _cmd.emplace(210, &UserConnection::cmdConnection);
    _cmd.emplace(225, &UserConnection::cmdJoinRoom);
    _cmd.emplace(235, &UserConnection::cmdQuitRoom);
    _cmd.emplace(300, &UserConnection::cmdCreateRoom);
    _cmd.emplace(350, &UserConnection::cmdDeleteRoom);
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

    asio::async_write(_socket, asio::buffer(std::string("")),
                        std::bind(&UserConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}

void UserConnection::handleWrite(const asio::error_code &error, size_t size)
{
    _message.consume(1024);
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

void UserConnection::sendError(int code, const std::string &msg)
{
    std::stringstream ss;
    ss << code;
    ss << " ";
    ss << msg;
    if (_debug) std::cout << "---> " << ss.str() << std::endl;
    ss << "\n";
    _socket.write_some(asio::buffer(ss.str()));
}

void UserConnection::broadcastTCP(const std::string &msg) const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();
    if (_debug) std::cout << "---> " << msg << " (boradcast)";
    for (auto user : *_userList) {
        user->getSocket().write_some(asio::buffer(msg));
    }
}

void UserConnection::broadcastTCPNotUser(const std::string &msg) const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();
    if (_debug) std::cout << "---> " << msg << " (broadcast not user)";
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
            std::string s = _isUDPOn ? std::to_string(_roomId) : "";
            user->getSocket().write_some(asio::buffer("290 " + s + "\n"));
        }
        else {
            if (_debug) std::cout << "user " << _userName <<  " disconnected from " <<
            _socket.remote_endpoint().address().to_string() << std::endl;
            if (_isUDPOn) {
                std::shared_ptr<ServerRoom> room = _servRef->getRoomById(_roomId);
                if (room != nullptr) {
                    room->removeUser(_id, _userName);
                }
            }
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
        if (_debug) std::cout << "tcp line recieved from " << _userName
        << " ip: " << _socket.remote_endpoint().address().to_string() << std::endl << "data: " + line << std::endl;
        std::vector<std::string> arg = SEPParsor::parseCommands(line);
        if (_cmd.count(std::atoi(arg[0].c_str()))) {
            UserConnection::factoryF func = _cmd[std::atoi(arg[0].c_str())];
            (this->*func)(arg);
        }
        else {
            sendError(500, "Unknown command.");
        }
    } else {
        checkDisconnection();
        return;
    }

    handleWrite(error, size);
}

std::string UserConnection::getUsername() const
{
    return (_userName);
}

bool UserConnection::isUsernameAvailable(const std::string &username) const
{
    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();

    for (auto itr : *_userList) {
        if (username == itr->getUsername()) {
            return (false);
        }
    }
    return (true);
}

///////////////////////////////////////////////////////////////
//-----------------------CMD_RESPONSES-----------------------//
///////////////////////////////////////////////////////////////

void UserConnection::cmdConnection(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {

        if (!isUsernameAvailable(arg[1])) {
            sendError(500, "Username already taken.");
            return;
        }

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
        if (_debug) std::cout << "---> " << ss.str() << std::endl;
        ss << "\n";
        _socket.send(asio::buffer(ss.str()));

    } else {
        sendError(500, "Missing arg in command.");
    }
}

void UserConnection::cmdCreateRoom(const std::vector<std::string> &arg)
{
    if (arg.size() >= 1) {
        int id = _servRef->addRoom();
        std::string response = "310 " + std::to_string(id) + "\n";
        broadcastTCP(response);
    } else {
        sendError(500, "Weird error.");
    }
}

void UserConnection::cmdJoinRoom(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        std::stringstream ss;
        std::shared_ptr<ServerRoom> room = _servRef->getRoomById(std::atoi(arg[1].c_str()));
        if (room != nullptr) {

            if (room->isPlayerInRoom(_id)) {
                sendError(500, "You are already in the room idiot.");
                return;
            }

            if (room->getNbUsers() == 4) {
                sendError(500, "Room is full.");
                return;
            }

            if (room->isGameStarted()) {
                sendError(500, "A game is currently running in this room.");
                return;
            }

            _roomId = room->getId();

            room->addUser(_id, _userName);
            ss << "230 ";
            ss << room->getId();
            ss << " ";
            ss << room->getPlayerFromId(_id)->getPort() - 1;
            ss << " ";
            ss << room->getPlayersName();
            ss << "\n";
            _socket.send(asio::buffer(ss.str()));
            _isUDPOn = true;
            broadcastTCPNotUser("280 " + std::to_string(room->getId()) + "\n");

        } else {
            sendError(500, "'id' of room does not exist.");
        }
    } else {
        sendError(500, "Missing arg in command.");
    }
}

void UserConnection::cmdQuitRoom(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        std::shared_ptr<ServerRoom> room = _servRef->getRoomById(std::atoi(arg[1].c_str()));
        std::stringstream ss;
        if (room != nullptr) {
            room->removeUser(_id, _userName);
            _isUDPOn = false;
            _roomId = -1;
            broadcastTCPNotUser("290 " + std::to_string(room->getId()) + "\n");
            _socket.send(asio::buffer("100\n"));
        } else {
            sendError(500, "'id' of room does not exist.");
        }
    } else {
        sendError(500, "Missing arg in command.");
    }
}

void UserConnection::cmdDeleteRoom(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        std::shared_ptr<ServerRoom> room = _servRef->getRoomById(std::atoi(arg[1].c_str()));

        if (room == nullptr) {
            sendError(500, "Impossible. Room does not exist.");
            return;
        }

        int ret = _servRef->deleteRoomById(std::atoi(arg[1].c_str()));
        if (ret == 1) {
            broadcastTCP("380 " + arg[1] + "\n");
        } else if (ret == 0) {
            sendError(500, "Impossible. Players are still in the room.");
        }

    } else {
        sendError(500, "Missing arg in command.");
    }
}

void UserConnection::cmdActions(const std::vector<std::string> &arg)
{
    if (arg.size() >= 2) {
        std::shared_ptr<ServerRoom> room = _servRef->getRoomById(_roomId);

        if (room == nullptr) {
            sendError(500, "Impossible. Room does not exist.");
            return;
        }

        std::shared_ptr<ServerPlayer> player = room->getPlayerFromId(_id);
        player->movePlayer(arg[1]);

    } else {
        sendError(500, "Missing arg in command.");
    }
}
