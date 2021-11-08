/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** SEPParsor
*/

#ifndef SEPPARSOR_HPP_
#define SEPPARSOR_HPP_

#include <iostream>
#include <vector>
#include <map>

class SEPParsor {
    public:
        SEPParsor();
        ~SEPParsor();
        std::vector<std::string> parseCommands(std::string command) const;
    protected:
    private:
        typedef std::string (SEPParsor::*factoryF)(const std::vector<std::string> &arg);

        std::map<int, factoryF> _cmd;
};

#endif /* !SEPPARSOR_HPP_ */
