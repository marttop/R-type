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

        /**
         * @brief Add a new user to the room.
         *
         * @param id new user's id.
         * @param username user's username.
         */
        void addUser(int id, const std::string &username);

        /**
         * @brief Remove user from the room.
         *
         * @param id id to broadcast.
         * @param username username to broadcast.
         */
        void removeUser(int id, const std::string &username);

        /**
         * @brief Get the Nb Users object
         *
         * @return ** int
         */
        int getNbUsers() const;

        /**
         * @brief Get the Players Name object
         *
         * @return ** std::string
         */
        std::string getPlayersName() const;

        /**
         * @brief Is the player in the room (By Id).
         *
         * @param id
         * @return true
         * @return false
         */
        bool isPlayerInRoom(int id) const;

        /**
         * @brief Returns the game thread ready to be detached.
         *
         * @return ** std::thread
         */
        std::thread startThread();

        /**
         * @brief Broadcast to all the players in the room.
         *
         * @param code SEP code
         * @param msg message
         */
        void broadCastUdp(const std::string &code, const std::string &msg);

        /**
         * @brief Get the Player From Id object
         *
         * @param id
         * @return ** std::shared_ptr<ServerPlayer>
         */
        std::shared_ptr<ServerPlayer> getPlayerFromId(int id) const;

        /**
         * @brief Returns true if everyone is ready in the room.
         *
         * @return true
         * @return false
         */
        bool isEveryoneReady() const;

        /**
         * @brief Returns true if the game has started.
         *
         * @return true
         * @return false
         */
        bool isGameStarted() const;

        /**
         * @brief Get the Id object
         *
         * @return ** int
         */
        int getId() const;

        /**
         * @brief Create a Entity Response object
         *
         * @param obj type of the object
         * @param action ction to be done (DELETE, CREATE, UDPATE).
         * @return ** std::string (response)
         */
        std::string createEntityResponse(std::shared_ptr<IEntity> obj, const std::string &action) const;

        /**
         * @brief Updates the entity
         *
         * @param obj entity
         * @return ** std::string
         */
        std::string updateEntity(std::shared_ptr<IEntity> obj) const;

        /**
         * @brief Checks asteroids collision with player
         *
         * @param player
         * @param entity
         */
        bool collideAsteroids(std::shared_ptr<ServerPlayer> player, std::shared_ptr<IEntity> entity);

        /**
         * @brief Who the fuck knows ? can't remember everything.
         *
         * @return ** std::string
         */
        std::string EntityAsShoot();

        /**
         * @brief Reset the timers.
         *
         */
        void resetTimers();

        //GAME

        /**
         * @brief Launches the game
         *
         */
        void playGame();

        /**
         * @brief Infinite loop of the game called by PlayGame().
         *
         */
        void updateLoop();

        /**
         * @brief Update players during the game.
         *
         * @return ** std::string
         */
        std::string updatePlayers() const;

        /**
         * @brief Create all the players
         *
         */
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
