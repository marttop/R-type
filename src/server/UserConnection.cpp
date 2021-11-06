/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Babel singelton
*/

#include "TcpConnection.hpp"

UserConnection::UserConnection(asio::io_context &io_context, std::vector<UserConnection::pointer> *userList, int id)
    : _socket(io_context), _userList(userList), _id(id)
{
}

asio::ip::tcp::socket &UserConnection::getSocket()
{
    return _socket;
}

void testFunc()
{
    // SEPCommands test= {0};
    // test.code = 100;
    // test.arg1 = "well done !";
    // test.arg2 = "";
    // test.arg3 = "";

    // char buff[sizeof(test) + 1];
    // std::memset(buff, '\0', sizeof(test) + 1);

    // std::memcpy(buff, &test, sizeof(test));

    // asio::mutable_buffer m = Serializer::serialize(test);
    // SEPCommands *coucou = Serializer::unSerialize((char *)m.data());
    // std::cout << coucou->arg1 << std::endl;
}

void UserConnection::startCommunication()
{

    for (auto user : *_userList) {
        if (&user->getSocket() != &_socket) {
            user->getSocket().write_some(asio::buffer("User connected with id: " + std::to_string(_id) + "\r\n"));
        }
    }

    asio::async_write(_socket, asio::buffer("Welcomeeeeeeeeeeeeeee !\r\n"),
                        std::bind(&UserConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));

    // _socket.write_some(asio::buffer("ass\r\n", 5));
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
    // std::cout << _message.;
    std::istream is(&_message);
    std::string line;
    std::getline(is, line);


    std::cout << "size: " << _userList->size() << std::endl;
    if (line != "") {
        for (auto user : *_userList) {
            if (&user->getSocket() != &_socket) {
                user->getSocket().write_some(asio::buffer("a fion has written\r\n"));
            }
        }
        std::cout << "line: " + line << std::endl;
    } else {
        int tmp = 0, i = 0;;
        for (auto user : *_userList) {
            if (&user->getSocket() != &_socket) {
                user->getSocket().write_some(asio::buffer("a fion has disconnected with id: " + std::to_string(_id) + "\r\n"));
            }
            else {
                tmp = i;
            }
            i++;
        }
        if (tmp != 0) {
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