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
            user->getSocket().write_some(asio::buffer("User connected with id: " + std::to_string(_id) + "\r\n"));
        }
    }

    asio::async_write(_socket, asio::buffer("Welcomeeeeeeeeeeeeeee !\r\n"),
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
    token = std::strtok(local_data, " \r\n");
    std::cout << data << std::endl;
    while (token != NULL) {
        token = std::strtok(NULL, " \r\n");
        std::cout << token << std::endl;
    }
}

void UserConnection::handleRead(const asio::error_code &error, size_t size)
{
    std::string sendMessage = "";
    std::istream is(&_message);
    std::string line;
    std::getline(is, line);

    std::vector<userConnectionPointer> *_userList = &_servRef->getUserList();

    std::cout << "size: " << _userList->size() << std::endl;
    if (line != "") {
        for (auto user : *_userList) {
            if (user->getId() != _id) {
                user->getSocket().write_some(asio::buffer("a fion has written\r\n"));
            }
        }
        std::cout << "line: " + line << std::endl;
    } else {
        int tmp = -1, i = 0;;
        for (auto user : *_userList) {
            if (user->getId() != _id) {
                user->getSocket().write_some(asio::buffer("a fion has disconnected with id: " + std::to_string(_id) + "\r\n"));
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
        return;
    }

    sendMessage = "hahahaha!\r\n";

    asio::async_write(_socket, asio::buffer(sendMessage),
                      std::bind(&UserConnection::handleWrite, shared_from_this(),
                                std::placeholders::_1,
                                std::placeholders::_2));
}