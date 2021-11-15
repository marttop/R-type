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
#include <ServerEntity.hpp>
#include <map>
#include <vector>

/*
    my singeltone loader insane du asssss
*/
// class EntityLoad {
//     public:
//         ~EntityLoad();

//         std::string error();

//         static EntityLoad &getEntityLoader() {
//              static EntityLoad instance;
//              return instance;
//         };
//         IEntity *loadEntityWithPath(const std::string &path);

//     protected:
//     private:
//         EntityLoad();

//         void open(const char *filepath);
//         int close();
//         void *sym(const std::string &name);

//         void *_handle;
// };

class EntityLoad {
    public:
        EntityLoad();
        ~EntityLoad();

        std::string                 error();

        void                        loadEntityWithPath(const std::string &path, const std::string &name);

        std::shared_ptr<IEntity>    createEntityWithName(const std::string &name);
        void                        destroyEntityWithName(const std::string &name, std::shared_ptr<IEntity> entity);

    protected:
    private:
        typedef IEntity*                    (*create)();
        typedef void                        (*destroy)(std::shared_ptr<IEntity>);

        void    *open(const char *filepath);
        int     close(void *handle);
        void    *sym(const std::string &name, void *handle);

        std::map<const std::string, create> creates;
        std::map<const std::string, destroy> destroys;
        std::vector<void *> dlOpens;
};

#endif /* !DL_HPP_ */
