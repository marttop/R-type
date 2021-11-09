/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** DL
*/

#include "EntityLoad.hpp"

EntityLoad::EntityLoad()
{
}

EntityLoad::~EntityLoad()
{
}

EntityLoad &EntityLoad::getEntityLoader()
{
    static EntityLoad instance;
    return instance;
}

std::string EntityLoad::error()
{
    return (dlerror());
}

void EntityLoad::open(const char *filepath)
{
    _handle = dlopen(filepath, RTLD_LOCAL | RTLD_LAZY);
    if (!_handle) {
        throw std::invalid_argument(this->error());
    }
}

int EntityLoad::close()
{
   return (dlclose(_handle));
}

void *EntityLoad::sym(const std::string &name)
{
    return (dlsym(_handle, name.c_str()));
}

IEntity *EntityLoad::loadEntityWithPath(const std::string &path)
{
    open(path.c_str());

    IEntity* (*create)();
    void (*destroy)(IEntity*);

    create = (IEntity* (*)())sym("allocator");
    destroy = (void (*)(IEntity*))sym("deleter");

    IEntity* myClass = (IEntity*)create();
    std::cout << "coucou" << std::endl;
    // destroy(myClass);
    // close();
    // il faudrait pouvoir les passé au IEntity pour qu'il destroy ca classe et close le dlOpen.

    return myClass;
}
