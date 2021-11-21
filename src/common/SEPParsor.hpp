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

        /**
         * @brief Parse the command line and returns an array of string
         * the code is in command[0].
         *
         * @param command command line.
         * @return ** std::vector<std::string> parsed response.
         */
        static std::vector<std::string> parseCommands(std::string command);
    protected:
    private:
};

#endif /* !SEPPARSOR_HPP_ */
