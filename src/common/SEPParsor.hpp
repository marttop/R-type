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
        static std::vector<std::string> parseCommands(std::string command);
    protected:
    private:
};

#endif /* !SEPPARSOR_HPP_ */
