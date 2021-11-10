/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** FontManager
*/

#ifndef FONTMANAGER_HPP_
#define FONTMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class FontManager {
public:
    ~FontManager();

    /**
     * @brief Get insatance of the FontManager singelton
     * 
     * @return ** FontManager& instance of FontManager 
     */
    static FontManager&     getFontManager();

    /**
     * @brief Get font, if font already load just return the font associeted to
     * 
     * @param path path to the font
     * @return sf::Font 
     */
    sf::Font                getFont(const std::string &path);


protected:
private:
    FontManager();

    std::map<const std::string, sf::Font> fonts;
};

#endif /* !FONTMANAGER_HPP_ */
