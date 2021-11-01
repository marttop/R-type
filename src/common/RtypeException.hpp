/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** RtypeException
*/

#ifndef RTYPEEXCEPTION_HPP_
#define RTYPEEXCEPTION_HPP_

#include <exception>
#include <string>

namespace rtype {
    class RtypeException : public std::exception {
        public:
            RtypeException(const std::string &what): _what(what) {};
            ~RtypeException() override = default;
            const char *what() const noexcept override {
                return _what.c_str();
            }
        private:
            std::string _what;
    };
};

#endif /* !RTYPEEXCEPTION_HPP_ */
