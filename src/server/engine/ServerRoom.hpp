/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerRoom
*/

#ifndef SERVERROOM_HPP_
#define SERVERROOM_HPP_

#include "UserConnection.hpp"
#include "ServerPlayer.hpp"
#include "EntityLoad.hpp"
#include "ServerMobSpawnConf.hpp"
#include <utility>
#include <thread>
#include <chrono>
#include "fstream"

class ServerPlayer;

class ServerRoom {
    public:
        ServerRoom(asio::io_context& io_context, int id, int portSeed, bool debug);
        ~ServerRoom();
        void addUser(int id, const std::string &username);
        void removeUser(int id, const std::string &username);
        int getNbUsers() const;
        std::string getPlayersName() const;
        bool isPlayerInRoom(int id) const;
        std::thread startThread();
        void broadCastUdp(const std::string &code, const std::string &msg);
        std::shared_ptr<ServerPlayer> getPlayerFromId(int id) const;
        bool isEveryoneReady() const;
        bool isGameStarted() const;
        int getId() const;

        std::string createEntityResponse(std::shared_ptr<IEntity> obj, const std::string &action) const;
        std::string updateEntity(std::shared_ptr<IEntity> obj) const;
        bool collideAsteroids(std::shared_ptr<ServerPlayer> player, std::shared_ptr<IEntity> entity);
        std::string EntityAsShoot();
        bool IsPlayers() const;

        void resetTimers();

        //GAME
        void playGame();
        void updateLoop();
        std::string updatePlayers() const;

        void createPlayers();

        bool _debug;
    protected:
    private:

        /**
         * @brief load all entities write in fileConfPath, need for this room
         *
         * @param fileConfPath path of conf file
         * @return ** void
         */
        void loadRoomEntities(const std::string &fileConfPath);

        /**
         * @brief creates all mobs from the vector _mobsRoomInfo and check if it's time to created it
         *
         * @return ** void
         */
        void createsEntities();

        /**
         * @brief update all created mobs
         *
         * @return ** std::string
         */
        std::string updateEntities();

        /**
         * @brief find the iterator with an if for use r
         *
         * @param list vector entity
         * @param id entity's id to find
         * @return ** std::vector<std::shared_ptr<IEntity>>::iterator
         */
        std::vector<std::shared_ptr<IEntity>>::iterator findIteratorWithId(std::vector<std::shared_ptr<IEntity>> list, const std::string &id) const;

        std::string deleteDeadEntities();

        std::vector<std::shared_ptr<ServerPlayer>> _playerList;
        asio::io_context &_io_context;
        asio::ip::udp::endpoint remote_endpoint_;
        void startGame();
        int _id;
        bool _isGameStarted;
        int _portSeed;
        int _timer;

        EntityLoad *_loader;
        std::vector<ServerMobSpawnConf> _entitiesRoomInfo;
        std::vector<std::shared_ptr<IEntity>> _entities;
};

#endif /* !SERVERROOM_HPP_ */
