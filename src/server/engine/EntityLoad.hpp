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

class EntityLoad {
    public:
        EntityLoad();
        ~EntityLoad();

        /**
         * @brief Return if error
         * 
         * @return ** std::string error
         */
        std::string                 error();

        /**
         * @brief Loads a new entity with the path and name.
         *
         * @param path 
         * @param name 
         * @return true (succes)
         * @return false (failure)
         */
        bool                        loadEntityWithPath(const std::string &path, const std::string &name);

        /**
         * @brief Create a Entity With Name object
         * 
         * @param name
         * @return ** std::shared_ptr<IEntity> 
         */
        std::shared_ptr<IEntity>    createEntityWithName(const std::string name);

        /**
         * @brief Deletes entity by name given.
         * 
         * @param name
         * @param entity
         */
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
