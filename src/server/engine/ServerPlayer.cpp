/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(const CustomRect &rect, asio::io_context &io_context, ServerRoom &roomRef, int port)
                            : ServerEntity(rect, "player", "", 5, 30), _io_context(io_context),
                            _socket(io_context,
                            asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
                            _roomRef(&roomRef), _port(port), _isReady(false)
{
    _userName = "";
    std::memset(_buffer, '\0', 1024);
    _canShoot = true;
    for (int i = 0; i < 5; i++) {
        _boolLand.push_back(false);
    }
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

void ServerPlayer::shoot()
{
    if (_canShoot) {
        static int id = 0;
        id++;
        std::string bId = _id + "B" + std::to_string(id);
        std::shared_ptr<IEntity> sp(new ServerBullet(CustomRect(20, 20,
            getPosition().first + 225, getPosition().second + 30), "playerbullet", bId, _rect._x));
        std::stringstream ss;
        ss.str("");
        ss.clear();
        ss << _roomRef->createEntityResponse(sp, "CREATE");
        std::cout << ss.str() << std::endl;
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
    _socket.async_receive_from(asio::buffer(_buffer), _receiverEndpoint,
                            std::bind(&ServerPlayer::handleReceive, this,
                                    std::placeholders::_1));
}

void ServerPlayer::sendData(const std::string &code, const std::string &msg)
{
    _socket.send_to(asio::buffer(code + " " + msg + "\n"), _receiverEndpoint);
}

void ServerPlayer::movePlayer(const std::string &direction, const std::string &action)
{
    double x = getPosition().first;
    double y = getPosition().second;
    if (direction == "UP") {
        _boolLand[0] = action == "START" ? true : false;
    }
    if (direction == "DOWN") {
        _boolLand[1] = action == "START" ? true : false;
    }
    if (direction == "LEFT") {
        _boolLand[2] = action == "START" ? true : false;
    }
    if (direction == "RIGHT") {
        _boolLand[3] = action == "START" ? true : false;
    } if (direction == "SPACE") {
        _boolLand[4] = action == "START" ? true : false;
    }
}

void ServerPlayer::handleReceive(const asio::error_code &error)
{
    if (_roomRef->_debug) std::cout << "udp line from " << _userName << ": " << _buffer;
    std::vector<std::string> args = SEPParsor::parseCommands(_buffer);
    if (args.size() == 2) {
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
    }
    else if (args.size() >= 3) {
        args[2].erase(remove(args[2].begin(), args[2].end(), '\n'), args[2].end());
        if (args[0] == "008") {
            movePlayer(args[1], args[2]);
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
    int itr = 0;
    std::stringstream ss;
    ss.str("");
    ss.clear();

    double x = getPosition().first;
    double y = getPosition().second;
    if (_isAlive) {
        if (_boolLand[0] == true) {
            setPosition(x, y += _speed);
        }
        if (_boolLand[1] == true) {
            setPosition(x, y -= _speed);
        }
        if (_boolLand[2] == true) {
            setPosition(x -= _speed, y);
        }
        if (_boolLand[3] == true) {
            setPosition(x += _speed, y);
        }
        if (_boolLand[4] == true) {
            shoot();
        }
    }

    auto i = std::begin(_ammo);
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