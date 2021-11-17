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

void Game::create(const sf::RenderWindow &window, char *udpBuf)
{
    _udpBuf = udpBuf;

    for (int i = 0; i < 5; i++)
        _inputs[i] = false;

    _alert.create(sf::Vector2f(window.getPosition().x + window.getSize().x / 2, window.getPosition().y + window.getSize().y / 2));

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

void Game::event(const sf::Event &event, const sf::RenderWindow &window, asio::ip::udp::socket &udpSocket)
{
    if (!_alert.isOpen()) {
        inputManagement(event, udpSocket);
    } else
        _alert.event(event, window);
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
void Game::udpUpdateEntity(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window)
{
    if (cmdUdp.size() > 0 && cmdUdp[0] == "007") {
        std::vector<std::string> entityCmd;
        int i = 0;
        for (auto it : cmdUdp) {
            if (it == cmdUdp.front()) continue;
            if (i == 8) {
                float posY = window.getSize().y - std::atof(entityCmd[4].c_str());
                sf::Color startColor = sf::Color::White;
                sf::Color endColor = sf::Color::White;
                selectPlayerColor(entityCmd, startColor, endColor);
                if (entityCmd[0] == "CREATE") {
                    _entityMap.insert(std::make_pair(
                        entityCmd[2],
                        _factory.getEntityByType(entityCmd[1], sf::Vector2f(std::atof(entityCmd[3].c_str()), posY), std::atof(entityCmd[7].c_str()), startColor, endColor)));
                }
                else if (entityCmd[0] == "UPDATE") {
                    // if (entityCmd[1] != "playerbullet") {
                        if (_entityMap.count(entityCmd[2]))
                            _entityMap[entityCmd[2]]->setPos(sf::Vector2f(std::atof(entityCmd[3].c_str()), posY));
                    // }
                }
                else if (entityCmd[0] == "DELETE") {
                    _entityMap.erase(entityCmd[2]);
                }
                i = 0;
                entityCmd.clear();
                continue;
            }
            entityCmd.push_back(it);
            i++;
        }
    }
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

void Game::update(const sf::RenderWindow &window, asio::ip::udp::socket &udpSocket)
{
    std::vector<std::string> cmdUdp = SEPParsor::parseCommands(_udpBuf);
    openAlert();
    if (!_alert.isOpen()) {
        udpUpdateEntity(cmdUdp, window);
        for (auto it : _entityMap)
            it.second->update();
    }
}

void Game::setAlert()
{
    _alert.open("Lost connection with the server.", false);
}

void Game::draw(sf::RenderWindow &window) const
{
    if (!_alert.isOpen()) {
        for (auto it : _entityMap) {
            it.second->draw(window);
        }
    }
    _alert.draw(window);
}