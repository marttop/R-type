/*
** EPITECH PROJECT, 2021
** G-JAM-001-NCE-0-2-jam-marton.szuts
** File description:
** Layer
*/

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "Entity.hpp"

class Layer : public Entity {
    public:
        Layer(const sf::Texture &texture, const sf::Vector2f &pos, const bool &active, const float &speed);
        ~Layer();

        /**
         * @brief Set the Active object
         *
         * @param activation
         */
        void setActive(const bool &activation);

        /**
         * @brief 
         * 
         * @return true
         * @return false 
         */
        bool isActive() const;

    protected:
    private:
        bool _isActive;
};

#endif /* !LAYER_HPP_ */