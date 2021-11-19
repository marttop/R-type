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
    for (auto it : dlOpens) {
        close(it);
    }
}

std::string EntityLoad::error()
{
    return (dlerror());
}

void *EntityLoad::open(const char *filepath)
{
    void *handle = dlopen(filepath, RTLD_LOCAL | RTLD_LAZY);
    if (!handle) {
        std::cout << this->error() << std::endl;;
    }
    return handle;
}

int EntityLoad::close(void *handle)
{
   return (dlclose(handle));
}

void *EntityLoad::sym(const std::string &name, void *handle)
{
    return (dlsym(handle, name.c_str()));
}

bool EntityLoad::loadEntityWithPath(const std::string &path, const std::string &name)
{
    void *handle = open(path.c_str());

    if (!handle) {
        return false;
    }

    IEntity *(*create)();
    void (*destroy)(std::shared_ptr<IEntity>);

    create = (IEntity *(*)())sym("allocator", handle);

    std::shared_ptr<IEntity> test(create());

    creates.insert(std::pair<const std::string, EntityLoad::create>(name, create));
    destroys.insert(std::pair<const std::string, EntityLoad::destroy>(name, destroy));
    dlOpens.push_back(handle);
    return true;
}

std::shared_ptr<IEntity> EntityLoad::createEntityWithName(const std::string name)
{
    std::shared_ptr<IEntity> entity(creates[name]());
    return entity;
}