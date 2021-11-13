/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerRoom
*/

#include "ServerRoom.hpp"

ServerRoom::ServerRoom(asio::io_context& io_context, int id, int portSeed, bool debug)
                                        : _io_context(io_context), _id(id), _portSeed(portSeed), _isGameStarted(false)
{
    _debug = debug;
}

ServerRoom::~ServerRoom()
{
}

void ServerRoom::addUser(int id, const std::string &username)
{
    static int port = _portSeed;
    port++;

    for (auto user : _playerList) {
        if (user->getId() != id) {
            user->sendData("001", username);
        }
    }


    std::shared_ptr<ServerPlayer> sp(new ServerPlayer(CustomRect(10, 10, 500, 500), _io_context, *this, port));
    sp->setId(id);
    sp->setUsername(username);
    sp->startUDP();
    _playerList.push_back(sp);

}

void ServerRoom::broadCastUdp(const std::string &code, const std::string &msg)
{
    for (auto itr : _playerList) {
        itr->sendData(code, msg);
    }
}

void ServerRoom::startGame()
{

}

bool ServerRoom::isEveryoneReady() const
{
    if (_playerList.size() > 0) {
        for (auto itr : _playerList) {
            if (!itr->isReady()) return (false);
        }
        return (true);
    }
    return (false);
}

int ServerRoom::getNbUsers() const
{
    return (_playerList.size());
}

void ServerRoom::playGame()
{
    int i = 5;
    while (i > 0) {
        broadCastUdp("005", std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!isEveryoneReady()) {
            return;
        }
        i--;
    }
    broadCastUdp("006", "");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    createPlayers();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    updateLoop();
}

bool ServerRoom::isGameStarted() const
{
    return (_isGameStarted);
}

std::thread ServerRoom::startThread()
{
    _isGameStarted = true;
    return std::thread(&ServerRoom::playGame, this);
}

void ServerRoom::removeUser(int id, const std::string &username)
{
    int tmp = -1, i = 0;
    for (auto user : _playerList) {
        if (user->getId() != id) {
            user->sendData("002", username);
        }
        else {
            user->closeUDP();
            tmp = i;
        }
        i++;
    }
    if (tmp != -1) {
        _playerList.erase(_playerList.begin() + tmp);
    }
}

bool ServerRoom::isPlayerInRoom(int id) const
{
    for (auto itr : _playerList) {
        if (itr->getId() == id) return (true);
    }
    return (false);
}

std::shared_ptr<ServerPlayer> ServerRoom::getPlayerFromId(int id) const
{
    for (auto itr : _playerList) {
        if (itr->getId() == id) return (itr);
    }
    return (nullptr);
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
        ss << (int)itr->isReady();
        ss << " ";
    }
    return (ss.str());
}

//GAME

void ServerRoom::createPlayers()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto itr : _playerList) {
        ss << " CREATE ";
        ss << itr->getType();
        ss << " ";
        ss << itr->getId();
        ss << " ";
        ss << itr->getPosition().first;
        ss << " ";
        ss << itr->getPosition().second;
        ss << " ";
        ss << itr->getDirection().first;
        ss << " ";
        ss << itr->getDirection().second;
        ss << " ";
        ss << itr->getSpeed();
        ss << " 00 ";
    }
    broadCastUdp("007", ss.str());
}

std::string ServerRoom::updatePlayers() const
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto itr : _playerList) {
        ss << " UPDATE ";
        ss << itr->getType();
        ss << " ";
        ss << itr->getId();
        ss << " ";
        ss << itr->getPosition().first;
        ss << " ";
        ss << itr->getPosition().second;
        ss << " ";
        ss << itr->getDirection().first;
        ss << " ";
        ss << itr->getDirection().second;
        ss << " ";
        ss << itr->getSpeed();
        ss << " 00 ";
    }
    return (ss.str());
}

void ServerRoom::updateLoop()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    while (1) {
        ss.str("");
        ss.clear();
        ss << updatePlayers();
        broadCastUdp("007", ss.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}