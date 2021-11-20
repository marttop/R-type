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

    bool validateIpAddress(const std::string &ipAddress);
    bool validatePort(const int &port);

protected:
private:
};

#endif /* !VALIDATEIP_HPP_ */
