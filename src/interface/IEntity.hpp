/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <string>
#include <iostream>
#include <memory>
#include "CustomRect.hpp"
#include <vector>

class IEntity {
    public:
        IEntity() = default;
        virtual ~IEntity() = default;

        /**
         * @brief Updates the entity
         *
         */
        virtual void update() = 0;

        /**
         * @brief Function not used
         *
         */
        virtual void sendData() = 0;

        /**
         *  @brief add life to an entity, this function can handle negative add
         *  @param lifeAdded number of life point sum to the actual life
         */
        virtual void addLifeEntity(int lifeAdded) = 0;

        /**
         * @brief Is the entity alive.
         *
         * @return true
         * @return false
         */
        virtual bool isAlive() const = 0;

        /**
         * @brief Set the Alive object
         *
         * @param life
         */
        virtual void setAlive(bool life) = 0;

        /**
         * @brief Clockring
         * 
         * @return true 
         * @return false 
         */
        virtual bool hasAClock() const = 0;

        /**
         * @brief Set ThreadCount
         * 
         * @return true 
         * @return false 
         */
        virtual void setThreadCount(int *threadCount) = 0;

        /**
         * @brief Is entity colliding with another.
         *
         * @param other
         * @return true
         * @return false
         */
        virtual bool isColliding(const std::shared_ptr<IEntity> &other) const = 0;

        /**
         * @brief isBoss
         * 
         * @return true 
         * @return false 
         */
        virtual bool isBoss() const = 0;

        /**
         * @brief isPickable
         * 
         * @return true 
         * @return false 
         */
        virtual bool isPickable() const = 0;

        /**
         * @brief isPlayerHarmful
         * 
         * @return true 
         * @return false 
         */
        virtual bool isPlayerHarmful() const = 0;

        /**
         * @brief isDropping
         * 
         * @return true 
         * @return false 
         */
        virtual bool isDropping() const = 0;

        /**
         * @brief isMobHarmful
         * 
         * @return true 
         * @return false 
         */
        virtual bool isMobHarmful() const = 0;

        /**
         * @brief isObstacle
         * 
         * @return true 
         * @return false 
         */
        virtual bool isObstacle() const = 0;

        /**
         * @brief Get the Rect object
         *
         * @return ** CustomRect
         */
        virtual CustomRect getRect() const = 0;

        /**
         * @brief Get the Type object
         *
         * @return ** std::string
         */
        virtual std::string getType() const = 0;

        /**
         * @brief Get the Id object
         *
         * @return ** std::string
         */
        virtual std::string getId() const = 0;

        /**
         * @brief Set the Id object
         *
         * @param id
         */
        virtual void setId(const std::string id) = 0;

        /**
         * @brief Get the Direction object
         *
         * @return ** std::pair<double, double> (x, y)
         */
        virtual std::pair<double, double> getDirection() const = 0;

        /**
         * @brief Get the Position object
         *
         * @return std::pair<double, double> (x, y)
         */
        virtual std::pair<double, double> getPosition() const = 0;

        /**
         * @brief Set the Position object
         *
         * @param x
         * @param y
         */
        virtual void setPosition(double x, double y) = 0;

        /**
         * @brief Set the Direction object
         *
         * @param x
         * @param y
         */
        virtual void setDirection(double x, double y) = 0;

        /**
         * @brief Get the Speed object
         *
         * @return ** double
         */
        virtual double getSpeed() const = 0;

        /**
         * @brief Get the Hp object
         *
         * @return ** int
         */
        virtual int getHp() const = 0;

        /**
         * @brief Get the Ammos object
         *
         * @return ** std::vector<std::shared_ptr<IEntity>>
         */
        virtual std::vector<std::shared_ptr<IEntity>> getAmmos() const = 0;

        /**
         * @brief Deletes all the ammos in the list of the entity.
         *
         */
        virtual void clearAmmos() = 0;

    protected:
    private:
};

#endif /* !IENTITY_HPP_ */
