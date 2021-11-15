/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect, asio::io_context &io_context, ServerRoom &roomRef, int port)
                            : ServerEntity(rect, "player"), _io_context(io_context),
                            _socketR(io_context,
                            asio::ip::udp::endpoint(asio::ip::udp::v4(), port - 1)),
                           _socketW(io_context,
                            asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
                            _roomRef(&roomRef), _port(port), _isReady(false)
{
    _userName = "";
    std::memset(_buffer, '\0', 1024);
    _canShoot = true;
}

ServerPlayer::~ServerPlayer()
{

}

void ServerPlayer::closeUDP()
{
    _socketR.close();
    _socketW.close();
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

void ServerPlayer::shoot()
{
    if (_canShoot) {
        static int id = 0;
        id++;
        std::string bId = _id + "B" + std::to_string(id);
        std::shared_ptr<IEntity> sp(new ServerBullet(CustomRect(20, 5,
            getPosition().first + 225, getPosition().second - 52), "playerbullet", bId));
        std::stringstream ss;
        ss.str("");
        ss.clear();
        ss << _roomRef->createEntityResponse(sp, "CREATE");
        _roomRef->broadCastUdp("007", ss.str());
        _canShoot = false;
        _ammo.push_back(sp);
    }
}

std::vector<std::shared_ptr<IEntity>> ServerPlayer::getAmmo()
{
    return (_ammo);
}

void ServerPlayer::startUDP()
{
    std::memset(_buffer, '\0', 1024);
    std::cout << "waiting" << std::endl;
    _socketR.async_receive_from(asio::buffer(_buffer), _receiverEndpointR,
                            std::bind(&ServerPlayer::openRead, this,
                                    std::placeholders::_1));
}

void ServerPlayer::openRead(const asio::error_code &error)
{
    std::memset(_buffer, '\0', 1024);
    if (_roomRef->_debug) std::cout << "udp line from " << _userName << ": " << _buffer;
    _socketW.async_receive_from(asio::buffer(_buffer), _receiverEndpointW,
                            std::bind(&ServerPlayer::handleReceive, this,
                                    std::placeholders::_1));
}

void ServerPlayer::sendData(const std::string &code, const std::string &msg)
{
    _socketW.send_to(asio::buffer(code + " " + msg + "\n"), _receiverEndpointW);
}

void ServerPlayer::movePlayer(const std::string &direction)
{
    double x = getPosition().first;
    double y = getPosition().second;
    if (direction == "UP") {
        setPosition(x, y + _speed);
    }
    else if (direction == "DOWN") {
        setPosition(x, y - _speed);
    }
    else if (direction == "LEFT") {
        setPosition(x - _speed, y);
    }
    else if (direction == "RIGHT") {
        setPosition(x + _speed, y);
    } else if (direction == "SPACE") {
        shoot();
    }
}

void ServerPlayer::handleReceive(const asio::error_code &error)
{
    if (_roomRef->_debug) std::cout << "udp line from " << _userName << ": " << _buffer;
    std::vector<std::string> args = SEPParsor::parseCommands(_buffer);
    if (args.size() >= 2) {
        args[1].erase(remove(args[1].begin(), args[1].end(), '\n'), args[1].end());
        if (args[0] == "003" && args[1] == "1") {
            _isReady = true;
            _roomRef->broadCastUdp("004", "1 " + _userName);
            if (_roomRef->isEveryoneReady()) {
                std::thread game = _roomRef->startThread();
                game.detach();
            }
        }
        else if (args[0] == "003" && args[1] == "0") {
            _roomRef->broadCastUdp("004", "0 " + _userName);
            _isReady = false;
        }
        else if (args[0] == "008") {
            movePlayer(args[1]);
        }
    }
    if (_socketR.is_open()) {
        std::memset(_buffer, '\0', 1024);
        _socketR.async_receive_from(asio::buffer(_buffer), _receiverEndpointR,
                                std::bind(&ServerPlayer::handleReceive, this,
                                        std::placeholders::_1));
    }
}

asio::ip::udp::socket &ServerPlayer::getSocket()
{
    return (_socketW);
}

void ServerPlayer::update()
{
    auto i = std::begin(_ammo);
    int itr = 0;
    std::stringstream ss;
    ss.str("");
    ss.clear();

    while (i != std::end(_ammo)) {
        i->get()->update();
        if (!i->get()->isAlive()) {
            ss << _roomRef->createEntityResponse(_ammo[itr], "DELETE");
            i = _ammo.erase(i);
        }
        else
            ++i, itr++;
    }
    if (ss.str() != "")
        _roomRef->broadCastUdp("007", ss.str());
}

void ServerPlayer::setUsername(const std::string &username)
{
    _userName = username;
}

std::string ServerPlayer::getUsername() const
{
    return (_userName);
}