/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect, asio::io_context &io_context, ServerRoom &roomRef, int port)
                            : ServerEntity(rect), _io_context(io_context),
                            _socket(io_context,
                            asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
                            _roomRef(&roomRef), _port(port), _isReady(false)
{
    _userName = "";
    std::memset(_buffer, '\0', 1024);
}

ServerPlayer::~ServerPlayer()
{

}

void ServerPlayer::closeUDP()
{
    _socket.close();
}

bool ServerPlayer::isReady() const
{
    return (_isReady);
}

int ServerPlayer::getPort() const
{
    return (_port);
}

void ServerPlayer::setIsReady(bool isReady)
{
    _isReady = isReady;
}

void ServerPlayer::startUDP()
{
    std::memset(_buffer, '\0', 1024);
    _socket.async_receive_from(asio::buffer(_buffer), _receiverEndpoint,
                            std::bind(&ServerPlayer::handleReceive, this,
                                    std::placeholders::_1));
}

void ServerPlayer::sendData(const std::string &code, const std::string &msg)
{
    _socket.send_to(asio::buffer(code + " " + msg + " \n"), _receiverEndpoint);
}

void ServerPlayer::handleReceive(const asio::error_code &error)
{
    std::cout << "udp line: " << _buffer;
    std::vector<std::string> args = SEPParsor::parseCommands(_buffer);
    if (args.size() >= 2) {
        if (args[0] == "003" && args[1] == "1") {
            _isReady = true;
            _roomRef->broadCastUdp("004", "1 " + _userName);
        }
        else if (args[0] == "003" && args[1] == "0") {
            _roomRef->broadCastUdp("004", "0 " + _userName);
            _isReady = false;
        }
    }
    else {
        if (args[0] == "005") {
            _roomRef->startThread();
        }
    }
    if (_socket.is_open()) {
        std::memset(_buffer, '\0', 1024);
        _socket.async_receive_from(asio::buffer(_buffer), _receiverEndpoint,
                                std::bind(&ServerPlayer::handleReceive, this,
                                        std::placeholders::_1));
    }
}

asio::ip::udp::socket &ServerPlayer::getSocket()
{
    return (_socket);
}

void ServerPlayer::update()
{
    std::cout << "I'm a player" << std::endl;
}

void ServerPlayer::setUsername(const std::string &username)
{
    _userName = username;
}

std::string ServerPlayer::getUsername() const
{
    return (_userName);
}