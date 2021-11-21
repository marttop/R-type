/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ValidateIp
*/

#ifndef VALIDATEIP_HPP_
#define VALIDATEIP_HPP_

#if defined (_WIN32)
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif
#include <string>

class ValidateIp {
public:
    ValidateIp();
    ~ValidateIp();

    /**
     * @brief Check if the ip is valid
     * 
     * @param ipAddress 
     * @return true 
     * @return false 
     */
    bool validateIpAddress(const std::string &ipAddress);

    /**
     * @brief Check if the port is valid
     * 
     * @param port 
     * @return true 
     * @return false 
     */
    bool validatePort(const int &port);

protected:
private:
};

#endif /* !VALIDATEIP_HPP_ */
