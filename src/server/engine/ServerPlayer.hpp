/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** ServerPlayer
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ServerBullet.hpp"
#include "ServerRoom.hpp"
#include <asio.hpp>
#include <time.h>

class ServerRoom;

class ServerPlayer :  public ServerEntity, std::enable_shared_from_this<ServerPlayer> {
    public:
        ServerPlayer(const CustomRect &rect, asio::io_context &io_context, ServerRoom &roomRef, int port);
        ~ServerPlayer();

        void update() override;

        /**
         * @brief Set the Username object
         *
         * @param username
         */
        void setUsername(const std::string &username);

        /**
         * @brief Get the Username object
         *
         * @return ** std::string
         */
        std::string getUsername() const;

        /**
         * @brief Get the isPushed bool
         *
         * @return ** bool
         */
        bool isPushed() const;

        /**
         * @brief Set the isPushed bool
         *
         * @param isPushed
         */
        void setIsPushed(const bool &isPushed);

        /**
         * @brief Get the Port object
         *
         * @return ** int
         */
        int getPort() const;

        /**
         * @brief Get the Socket object
         *
         * @return ** asio::ip::udp::socket&
         */
        asio::ip::udp::socket &getSocket();

        /**
         * @brief Starts udp commincation in the room.
         *
         */
        void startUDP();

        /**
         * @brief Is the user ready.
         *
         * @return true
         * @return false
         */
        bool isReady() const;

        /**
         * @brief Set the Is Ready object
         *
         * @param isReady
         */
        void setIsReady(bool isReady);

        /**
         * @brief Sends data to the user (UDP only).
         *
         * @param code SEP code (UDP)
         * @param msg message
         */
        void sendData(const std::string &code, const std::string &msg);

        /**
         * @brief Boradcast UDP data to everyone in the room but not the user
         *
         */
        void broadcastUDPNotSelf();

        /**
         * @brief Async recieve for the UDP user
         *
         * @param error error code (asio)
         */
        void handleReceive(const asio::error_code &error);

        /**
         * @brief Close the udp socket
         *
         */
        void closeUDP();

        /**
         * @brief Moves the player
         *
         * @param direction
         * @param action
         */
        void movePlayer(const std::string &direction, const std::string &action);

        /**
         * @brief Get the Ammo object
         *
         * @return ** std::vector<std::shared_ptr<IEntity>>
         */
        std::vector<std::shared_ptr<IEntity>> getAmmo();

        /**
         * @brief Creates a shooting entity in the player.
         *
         */
        void shoot();
        bool _canShoot;

    protected:
    private:
        std::string _userName;
        asio::ip::udp::socket _socket;
        asio::io_context &_io_context;
        asio::ip::udp::endpoint _receiverEndpoint;
        ServerRoom *_roomRef;
        std::vector<std::shared_ptr<IEntity>> _ammo;
        bool _isReady;
        char _buffer[1024];
        int _port;
        std::vector<bool> _boolLand;
        bool _isShooting;
        bool _isPushed;
};

#endif /* !PLAYER_HPP_ */
