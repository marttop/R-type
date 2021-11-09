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
#include <IEntity.hpp>

class EntityLoad {
    public:
        ~EntityLoad();

        std::string error();

        static EntityLoad &getEntityLoader();

        IEntity *loadEntityWithPath(const std::string &path);

    protected:
    private:
        EntityLoad();

        void open(const char *filepath);
        int close();
        void *sym(const std::string &name);

        void *_handle;
};

#endif /* !DL_HPP_ */
