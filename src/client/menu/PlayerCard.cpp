/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** PlayerCard
*/

#include "PlayerCard.hpp"

PlayerCard::PlayerCard()
{
}

PlayerCard::~PlayerCard()
{
}

void PlayerCard::create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name, const std::string &ready, const sf::Vector2f &factors)
{
    _background.setSize(sf::Vector2f(size.x, size.y));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));

    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");

    _name.setString(name + '\n');
    _name.setScale(factors);
    _name.setFont(_font);
    _name.setOrigin(sf::Vector2f(_name.getOrigin().x, _name.getGlobalBounds().height / 3));
    _name.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 10, _background.getPosition().y + _background.getSize().y / 1.9));

    _readyTexture = AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/ready.png");
    _notReadyTexture = AssetManager<sf::Texture>::getAssetManager().getAsset("assets/menu/notready.png");

    _ready.setTexture(_notReadyTexture);
    _ready.setOrigin(sf::Vector2f(_ready.getTextureRect().width / 2, _ready.getTextureRect().height / 2));
    _ready.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 1.15, _background.getPosition().y + _background.getSize().y / 2));

}

std::string PlayerCard::getName() const
{
    return (_name.getString());
}

void PlayerCard::setReady(const std::string &state)
{
    if (state == "1")
        _ready.setTexture(_readyTexture);
    else
        _ready.setTexture(_notReadyTexture);
}

void PlayerCard::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(_name);
    window.draw(_ready);
}

sf::Vector2f PlayerCard::getPosition() const
{
    return (_background.getPosition());
}

void PlayerCard::setPosition(const sf::Vector2f &pos)
{
    _background.setPosition(pos);
    _name.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 10, _background.getPosition().y + _background.getSize().y / 1.9));
    _ready.setPosition(sf::Vector2f(_background.getPosition().x + _background.getSize().x / 1.15, _background.getPosition().y + _background.getSize().y / 2));
}

sf::Vector2f PlayerCard::getSize() const
{
    return (_background.getSize());
}