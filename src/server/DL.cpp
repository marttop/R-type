/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** DL
*/

#include "DL.hpp"

DL::DL()
{
}

DL::~DL()
{
}

std::string DL::error()
{
    return (dlerror());
}

void DL::open(char *filepath, int flag)
{
    _handle = dlopen(filepath, flag);
    if (!_handle) {
        throw std::invalid_argument(this->error());
    }
}

int DL::close()
{
   return (dlclose(_handle));
}

void *DL::sym(const std::string &name)
{
    return (dlsym(_handle, name.c_str()));
}
