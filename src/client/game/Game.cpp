/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::create(sf::RenderWindow &window, asio::ip::udp::socket &udpSocket)
{
    std::memset(_udpBuf, '\0', BUFF_SIZE);

    for (int i = 0; i < 5; i++)
        _inputs[i] = false;

    _window = &window;
    _udpSocket = &udpSocket;
    _alert.create(sf::Vector2f(_window->getPosition().x + _window->getSize().x / 2, _window->getPosition().y + _window->getSize().y / 2));

    _playerCount = 0;
}

void Game::inputManagement(const sf::Event &event, asio::ip::udp::socket &udpSocket)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up && !_inputs[UP]) {
            _inputs[UP] = true;
            udpSocket.send(asio::buffer("008 UP START\n"));
        }
        if (event.key.code == sf::Keyboard::Left && !_inputs[LEFT]) {
            _inputs[LEFT] = true;
            udpSocket.send(asio::buffer("008 LEFT START\n"));
        }
        if (event.key.code == sf::Keyboard::Down && !_inputs[DOWN]) {
            _inputs[DOWN] = true;
            udpSocket.send(asio::buffer("008 DOWN START\n"));
        }
        if (event.key.code == sf::Keyboard::Right && !_inputs[RIGHT]) {
            _inputs[RIGHT] = true;
            udpSocket.send(asio::buffer("008 RIGHT START\n"));
        }
        if (event.key.code == sf::Keyboard::Space && !_inputs[SPACE]) {
            _inputs[SPACE] = true;
            udpSocket.send(asio::buffer("008 SPACE START\n"));
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up && _inputs[UP]) {
            _inputs[UP] = false;
            udpSocket.send(asio::buffer("008 UP STOP\n"));
        }
        if (event.key.code == sf::Keyboard::Left && _inputs[LEFT]) {
            _inputs[LEFT] = false;
            udpSocket.send(asio::buffer("008 LEFT STOP\n"));
        }
        if (event.key.code == sf::Keyboard::Down && _inputs[DOWN]) {
            _inputs[DOWN] = false;
            udpSocket.send(asio::buffer("008 DOWN STOP\n"));
        }
        if (event.key.code == sf::Keyboard::Right && _inputs[RIGHT]) {
            _inputs[RIGHT] = false;
            udpSocket.send(asio::buffer("008 RIGHT STOP\n"));
        }
        if (event.key.code == sf::Keyboard::Space && _inputs[SPACE]) {
            _inputs[SPACE] = false;
            udpSocket.send(asio::buffer("008 SPACE STOP\n"));
        }
    }
}

void Game::event(const sf::Event &event, asio::ip::udp::socket &udpSocket)
{
    if (!_alert.isOpen()) {
        inputManagement(event, udpSocket);
    } else
        _alert.event(event, *_window);
}

void Game::selectPlayerColor(std::vector<std::string> &entityCmd, sf::Color &startColor, sf::Color &endColor)
{
    if (entityCmd[1] != "player") return;
    if (_playerCount == 0) {
        startColor = sf::Color(0, 0, 255, 255);
        endColor = sf::Color(30,144,255);
    } else if (_playerCount == 1) {
        startColor = sf::Color(255, 0, 0, 255);
        endColor = sf::Color(139, 0, 0, 255);
    } else if (_playerCount == 2) {
        startColor = sf::Color(255, 255, 0, 255);
        endColor = sf::Color(255, 215, 0, 255);
    } else if (_playerCount == 3) {
        startColor = sf::Color(0, 255, 0, 255);
        endColor = sf::Color(0, 128, 0, 255);
    }
    _playerCount++;
}

/* 0 == ACTION, 1 == TYPE, 2 == ID, 3 == POSX, 4 == POSY, 5 == DIRX, 6 == DIRY, 7 == SPEED */
void Game::udpUpdateEntity(std::vector<std::string> &cmdUdp)
{
    if (cmdUdp.size() > 0 && cmdUdp[0] == "007") {
        _lock.lock();
        std::vector<std::string> entityCmd;
        int i = 0;
        for (auto it : cmdUdp) {
            if (it == cmdUdp.front()) continue;
            if (i == 8) {
                float posY = _window->getSize().y - std::atof(entityCmd[4].c_str());
                sf::Color startColor = sf::Color::Red;
                sf::Color endColor = sf::Color::Green;
                selectPlayerColor(entityCmd, startColor, endColor);
                if (entityCmd[0] == "CREATE") {
                    _entityMap.insert(std::make_pair(
                        entityCmd[2],
                        _factory.getEntityByType(entityCmd[1], sf::Vector2f(std::atof(entityCmd[3].c_str()), posY), std::atof(entityCmd[7].c_str()), startColor, endColor)));
                }
                else if (entityCmd[0] == "UPDATE" && _entityMap.count(entityCmd[2]) > 0) {
                    // if (entityCmd[1] != "playerbullet") {
                        if (_entityMap.count(entityCmd[2]))
                            _entityMap[entityCmd[2]]->setPos(sf::Vector2f(std::atof(entityCmd[3].c_str()), posY));
                    // }
                }
                else if (entityCmd[0] == "DELETE" && _entityMap.count(entityCmd[2]) > 0) {
                    _entityMap[entityCmd[2]]->setIsAlive(false);
                }
                i = 0;
                entityCmd.clear();
                continue;
            }
            entityCmd.push_back(it);
            i++;
        }
        _lock.unlock();
    }
}

std::thread Game::startThread(const asio::error_code &error)
{
    return std::thread(&Game::handleRead, this, error);
}

void Game::openAlert()
{
    std::string stringBuf(_udpBuf);
    if (stringBuf.size() > 0 && stringBuf.find("500") == 0) {
        stringBuf.erase(0, 4);
        if (stringBuf.find('\n') != std::string::npos)
            stringBuf.pop_back();
        _alert.open(stringBuf, true);
    }
}

void Game::update()
{
    std::vector<std::string> cmdUdp = SEPParsor::parseCommands(_udpBuf);
    openAlert();
    if (!_alert.isOpen()) {
        udpUpdateEntity(cmdUdp);
        for (auto it : _entityMap)
            it.second->update();
    }
}

void Game::handleRead(const asio::error_code &error)
{
    asio::error_code error2;
    while (1) {
        if (std::strlen(_udpBuf) > 0) {
            update();
            // std::cout << _udpBuf;
        }
        std::memset(_udpBuf, '\0', BUFF_SIZE);
        // _udpSocket->async_receive(asio::buffer(_udpBuf), std::bind(&Game::handleRead, this,
        //                                     std::placeholders::_1));
        size_t len = 0;
        len = _udpSocket->receive(asio::buffer(_udpBuf), 0, error2);
    }
}

void Game::setAlert()
{
    _alert.open("Lost connection with the server.", false);
}

void Game::draw()
{
    // if (!_alert.isOpen()) {
    //     for (auto it : _entityMap) {
    //         it.second->draw(*_window);
    //         if (!it.second->isAlive()) {
    //         }
    //     }
    // }
    auto i = std::begin(_entityMap);
    while (i != std::end(_entityMap)) {
        i->second->draw(*_window);
        if (!i->second->isAlive()) {
            i = _entityMap.erase(i);
        }
        else
            ++i;
    }
    _alert.draw(*_window);
}