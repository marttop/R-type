/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** DL
*/

#ifndef DL_HPP_
#define DL_HPP_

#include <dlfcn.h>
#include <string>
#include <iostream>

class DL {
    public:
        DL();
        ~DL();

        std::string error();
        void open(char *filepath, int flag);
        int close();
        void *sym(const std::string &name);
    protected:
    private:
        void *_handle;
};

#endif /* !DL_HPP_ */
