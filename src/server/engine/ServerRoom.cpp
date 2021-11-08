/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerRoom
*/

#include "ServerRoom.hpp"

ServerRoom::ServerRoom(asio::io_context& io_context, int id) : _io_context(io_context), _id(id)
{
}

ServerRoom::~ServerRoom()
{
}

void ServerRoom::addUser(int id, const std::string &username)
{
    std::shared_ptr<ServerPlayer> sp(new ServerPlayer(CustomRect(10, 10), _io_context));
    sp->setId(id);
    sp->setUsername(username);
    sp->startUDP();
    _playerList.push_back(sp);
}

int ServerRoom::getNbUsers() const
{
    return (_playerList.size());
}

void ServerRoom::removeUser(int id)
{
    int tmp = -1, i = 0;
    for (auto user : _playerList) {
        if (user->getId() != _id) {
            user->getSocket().send(asio::buffer("250 " + std::to_string(_id) + "\n"));
        }
        else {
            tmp = i;
        }
        i++;
    }
    if (tmp != -1) {
        _playerList.erase(_playerList.begin() + tmp);
    } else {
        _playerList.clear();
    }
}

int ServerRoom::getId() const
{
    return (_id);
}

std::string ServerRoom::getPlayersName() const
{
    std::stringstream ss;
    ss << "";
    for (auto itr : _playerList) {
        ss << itr->getUsername();
        ss << " ";
    }
    return (ss.str());
}