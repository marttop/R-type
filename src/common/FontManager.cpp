/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** FontManager
*/

#include "FontManager.hpp"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

FontManager &FontManager::getFontManager()
{
    static FontManager instance = FontManager();
    return instance;
}

sf::Font FontManager::getFont(const std::string &path)
{
    sf::Font font;

    if (fonts.find(path) != fonts.end()) {
        return fonts[path];
    }

    if (font.loadFromFile(path)) {
        fonts.insert(std::pair<std::string, sf::Font>(path, font));
    }

    return font;
}