/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerRoom
*/

#include "ServerRoom.hpp"

ServerRoom::ServerRoom(asio::io_context& io_context, int id, int portSeed, bool debug)
                                        : _io_context(io_context), _id(id), _portSeed(portSeed), _isGameStarted(false), _loader(EntityLoad())
{
    _debug = debug;
    _timer = 0;
    loadRoomEntities("RoomConfFile/ConfTest.txt");
}

ServerRoom::~ServerRoom()
{
}

// loader

void ServerRoom::loadRoomEntities(const std::string &FilePath)
{
    std::string line;
    std::ifstream myfile(FilePath);
    if (myfile.is_open())
    {
        while (std::getline(myfile,line)) {
            if (line[0] == '#') continue;
            std::vector<std::string> parsedTab = SEPParsor::parseCommands(line);

            if (!_loader.loadEntityWithPath(parsedTab[0], parsedTab[1])) {
                continue;
            }

            std::cout << "load entity: " << parsedTab[1] << std::endl;
            _entitiesRoomInfo.push_back(ServerMobSpawnConf(parsedTab[1], std::atoi(parsedTab[2].c_str()), std::atoi(parsedTab[3].c_str())));
        }
        myfile.close(); 
    }
}

void ServerRoom::addUser(int id, const std::string &username)
{
    static int port = _portSeed;
    port++;

    for (auto user : _playerList) {
        if (user->getId() != std::to_string(id)) {
            user->sendData("001", username);
        }
    }


    std::shared_ptr<ServerPlayer> sp(new ServerPlayer(CustomRect(232, 96, 500, 500), _io_context, *this, port));
    sp->setId(std::to_string(id));
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
    int i = 3;
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
        if (user->getId() != std::to_string(id)) {
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
        if (itr->getId() == std::to_string(id)) return (true);
    }
    return (false);
}

std::shared_ptr<ServerPlayer> ServerRoom::getPlayerFromId(int id) const
{
    for (auto itr : _playerList) {
        if (itr->getId() == std::to_string(id)) return (itr);
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

std::string ServerRoom::createEntityResponse(
                    std::shared_ptr<IEntity> obj, const std::string &action) const
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    ss << " " + action + " ";
    ss << obj->getType();
    ss << " ";
    ss << obj->getId();
    ss << " ";
    ss << obj->getPosition().first;
    ss << " ";
    ss << obj->getPosition().second;
    ss << " ";
    ss << obj->getDirection().first;
    ss << " ";
    ss << obj->getDirection().second;
    ss << " ";
    ss << obj->getSpeed();
    ss << " 00 ";
    return (ss.str());
}

void ServerRoom::createsEntities() {
    static int id = 0;
    std::stringstream ss;
    ss.str("");
    ss.clear();

    for (auto entity : _entitiesRoomInfo) {
        if (_timer == entity.getTimeToSpawn()) {
            std::cout << entity.getNumberOfEntities() << std::endl;
            for (int i = 0; i < entity.getNumberOfEntities(); i++) {
                auto createdEntity = _loader.createEntityWithName(entity.getTypeEntities());
                createdEntity->setId("E" + std::to_string(id));
                id += 1;
                _entities.push_back(createdEntity);
                ss << createEntityResponse(createdEntity, "CREATE");
            }
        }
    }
    if (ss.str() != "")
        broadCastUdp("007", ss.str());
}

std::string ServerRoom::updateEntities()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto entity : _entities) {
        entity->update();
        ss << createEntityResponse(entity, "UPDATE");
    }
    return (ss.str());
}

void ServerRoom::createPlayers()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto itr : _playerList) {
        ss << createEntityResponse(itr, "CREATE");
    }
    broadCastUdp("007", ss.str());
}

std::string ServerRoom::updatePlayers() const
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto itr : _playerList) {
        itr->update();
        ss << createEntityResponse(itr, "UPDATE");
        // for (auto bullet : itr->getAmmo()) {
        //     ss << createEntityResponse(bullet, "UPDATE");
        // }
    }
    return (ss.str());
}

void ServerRoom::resetTimers()
{
    for (auto itr : _playerList) {
        itr->_canShoot = true;
    }
}

void ServerRoom::updateLoop()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    while (1) {
        ss.str("");
        ss.clear();

        createsEntities();

        if (_timer % 7 == 0) {
            resetTimers();
        }
        ss << updatePlayers();
        // ss << updateEntities();
        broadCastUdp("007", ss.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(22));
        _timer++;
    }
}