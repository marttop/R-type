/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** SEPParsor
*/

#include "SEPParsor.hpp"

SEPParsor::SEPParsor()
{
    // _cmd.emplace(210, &SEPParsor::requestUserCreation);
}

SEPParsor::~SEPParsor()
{
}

std::vector<std::string> SEPParsor::parseCommands(std::string command) const
{
    std::vector<std::string> arr;
    std::size_t pos = 0;
    std::string word;
    int lenght = 0;
    while ((pos = command.find(" ")) != std::string::npos) {
        word = command.substr(0, pos);
        if (word != "")
            arr.push_back(word);
        for (int i = pos; command[i] == ' '; i++)
            lenght++;
        command.erase(0, pos + lenght);
        lenght = 0;
    }
    if (command != "")
        arr.push_back(command);
    arr[arr.size() - 1].erase(arr[arr.size() - 1].size() - 1, 2);
    return arr;
}