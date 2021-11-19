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
    _loader = new EntityLoad();
    _debug = debug;
    _timer = 0;
    loadRoomEntities("RoomConfFile/ConfTest.txt");
    _loader->loadEntityWithPath("./src/server/entities/BossBullet/BossBullet.so", "BossBullet");
    _loader->loadEntityWithPath("./src/server/entities/Heal/Heal.so", "Heal");
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

            if (!_loader->loadEntityWithPath(parsedTab[0], parsedTab[1])) {
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
    ss << " ";
    ss << obj->getHp();
    ss << " 00 ";
    return (ss.str());
}

void ServerRoom::createsEntities()
{
    static int id = 0;
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for (auto entity : _entitiesRoomInfo) {
        if (_timer == entity.getTimeToSpawn()) {
            std::cout << entity.getNumberOfEntities() << std::endl;
            for (int i = 0; i < entity.getNumberOfEntities(); i++) {
                auto createdEntity = _loader->createEntityWithName(entity.getTypeEntities());
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

std::vector<std::shared_ptr<IEntity>>::iterator ServerRoom::findIteratorWithId(std::vector<std::shared_ptr<IEntity>> list, const std::string &id) const
{
    std::vector<std::shared_ptr<IEntity>>::iterator it = list.begin();
    for (;it != list.end(); ++it) {
        if (it->get()->getId() == id) {
            break;
        }
    }
    return it;
}

std::string ServerRoom::deleteDeadEntities()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    int index = 0;

    for (auto it = _entities.begin(); it != _entities.end();) {
        if (it->get()->isAlive() == false) {
            ss << createEntityResponse(_entities.at(index), "DELETE");
            if (it->get()->getType() == "BidosSlaves") {
                if (std::rand() % 100 > 50) {
                    auto createdEntity = _loader->createEntityWithName("Heal");
                    createdEntity->setPosition(it->get()->getPosition().first, it->get()->getPosition().second);
                    _entities.push_back(createdEntity);
                    ss << createEntityResponse(createdEntity, "CREATE");
                }
            }
           it = _entities.erase(it);

        } else {
            ++it;
            index += 1;
        }
    }

    return ss.str();
}

std::string ServerRoom::EntityAsShoot()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    std::vector<std::shared_ptr<IEntity>> tmp;

    for (auto entity : _entities) {
        for (auto bullet : entity->getAmmos()) {
            tmp.push_back(bullet);
            ss << createEntityResponse(bullet, "CREATE");

        }
        entity->clearAmmos();
    }

    _entities.insert( _entities.end(), tmp.begin(), tmp.end() );

    return ss.str();
}

std::string ServerRoom::updateEntities()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    std::string tmp;
    static int timer = 0;

    for (auto entity : _entities) {
        entity->update();

        for (auto player : _playerList) {
            if (timer % 7 == 0 && entity->getType() == "BossBullet" && player->isColliding(entity)) {
                timer = 0;
                if (player->isAlive()) {
                    player->addLifeEntity(-1);
                    if (!player->isAlive()) {
                        ss << createEntityResponse(player, "DELETE");
                    }
                }
            }
            for (auto playerBullet : player->getAmmo()) {
                if (entity->isColliding(playerBullet) && entity->getType() != "BossBullet") {
                    playerBullet->setAlive(false);
                    entity->addLifeEntity(-1);
                }
            }
        }
        ss << createEntityResponse(entity, "UPDATE");
    }

    timer++;

    ss << EntityAsShoot();
    ss << deleteDeadEntities();

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
        if (itr->isAlive()) {
            ss << createEntityResponse(itr, "UPDATE");
        }
        for (auto bullet : itr->getAmmo()) {
            ss << createEntityResponse(bullet, "UPDATE");
        }
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
        ss << updateEntities();
        broadCastUdp("007", ss.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
        _timer++;
    }
}