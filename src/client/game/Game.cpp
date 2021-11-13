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

    for (int i = 0; i < 4; i++)
        _direction[i] = false;

    _alert.create(sf::Vector2f(window.getPosition().x + window.getSize().x / 2, window.getPosition().y + window.getSize().y / 2));
}

void Game::inputManagement(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            _direction[UP] = true;
        if (event.key.code == sf::Keyboard::Left)
            _direction[LEFT] = true;
        if (event.key.code == sf::Keyboard::Down)
            _direction[DOWN] = true;
        if (event.key.code == sf::Keyboard::Right)
            _direction[RIGHT] = true;
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up)
            _direction[UP] = false;
        if (event.key.code == sf::Keyboard::Left)
            _direction[LEFT] = false;
        if (event.key.code == sf::Keyboard::Down)
            _direction[DOWN] = false;
        if (event.key.code == sf::Keyboard::Right)
            _direction[RIGHT] = false;
    }
}

void Game::sendDirection(boost::asio::ip::udp::socket &udpSocket)
{
    if (_direction[RIGHT])
        udpSocket.send(boost::asio::buffer("008 RIGHT\n"));
    if (_direction[UP])
        udpSocket.send(boost::asio::buffer("008 UP\n"));
    if (_direction[LEFT])
        udpSocket.send(boost::asio::buffer("008 LEFT\n"));
    if (_direction[DOWN])
        udpSocket.send(boost::asio::buffer("008 DOWN\n"));
}

void Game::event(const sf::Event &event, const sf::RenderWindow &window, boost::asio::ip::udp::socket &udpSocket)
{
    if (!_alert.isOpen()) {
        inputManagement(event);
    } else
        _alert.event(event, window);
}

void Game::updateEntity(std::vector<std::string> &cmdUdp, const sf::RenderWindow &window)
{
    if (cmdUdp.size() > 0 && cmdUdp[0] == "007") {
        std::vector<std::string> entityCmd;
        int i = 0;
        for (auto it : cmdUdp) {
            if (it == cmdUdp.front()) continue;
            if (i == 8) {
                float posY = window.getSize().y - std::atof(entityCmd[4].c_str());
                if (entityCmd[0] == "CREATE") {
                    std::cout << entityCmd[1] << std::endl;
                    _entityMap.insert(std::make_pair(
                        entityCmd[2],
                        _factory.getEntityByType(entityCmd[1], sf::Vector2f(std::atof(entityCmd[3].c_str()), posY), entityCmd[2])));
                }
                if (entityCmd[0] == "UPDATE")
                    _entityMap[entityCmd[2]]->setPos(sf::Vector2f(std::atof(entityCmd[3].c_str()), posY));
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

void Game::update(const sf::RenderWindow &window, boost::asio::ip::udp::socket &udpSocket)
{
    std::vector<std::string> cmdUdp = SEPParsor::parseCommands(_udpBuf);
    openAlert();
    if (!_alert.isOpen()) {
        updateEntity(cmdUdp, window);
        sendDirection(udpSocket);
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