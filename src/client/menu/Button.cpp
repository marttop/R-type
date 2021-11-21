/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** Button
*/

#include "Button.hpp"

Button::Button()
{
    _text = nullptr;
}

Button::~Button()
{
    if (_text)
        delete _text;
}

void Button::create(const sf::Vector2f &pos, const std::string &text, const sf::Vector2f &offset, const sf::Vector2f &factors)
{
    _outline = sf::Color::White;

    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(_outline);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));

    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");

    _offset = offset;

    _clickBuf = AssetManager<sf::SoundBuffer>::getAssetManager().getAsset("assets/sounds/button_click.ogg");
    _click.setBuffer(_clickBuf);
    _click.setVolume(50);

    _hoverBuf = AssetManager<sf::SoundBuffer>::getAssetManager().getAsset("assets/sounds/menu_hover.ogg");
    _hover.setBuffer(_hoverBuf);
    _hover.setVolume(50);

    _text = new sf::Text;
    _text->setString(text);
    _text->setScale(factors);
    _text->setFont(_font);
    _text->setOrigin(sf::Vector2f(_text->getGlobalBounds().left + _text->getGlobalBounds().width / 2, _text->getGlobalBounds().top + _text->getGlobalBounds().height / 2));
    _text->setPosition(sf::Vector2f(_background.getPosition().x + _offset.x, _background.getPosition().y + _offset.y));

    _background.setSize(sf::Vector2f(_text->getGlobalBounds().width * 1.6, _text->getGlobalBounds().height * 2));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));
}

void Button::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    window.draw(*_text);
}

void Button::setPosition(const sf::Vector2f &pos)
{
    _background.setPosition(pos);
    _text->setPosition(sf::Vector2f(pos.x + _offset.x, pos.y + _offset.y));
}

bool Button::update(const sf::RenderWindow &window, const bool &isDrawn)
{
    bool check = false;
    if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if (_outline == sf::Color::White && isDrawn)
            _hover.play();
        _outline = sf::Color::Yellow;
        _background.setOutlineColor(_outline);
        check = true;
    }
    else {
        _outline = sf::Color::White;
        _background.setOutlineColor(_outline);
    }
    return (check);
}

bool Button::event(const sf::Event &event, const sf::RenderWindow &window)
{
    bool clicked = false;
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _background.setFillColor(sf::Color::White);
            _text->setFillColor(sf::Color::Black);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        _background.setFillColor(sf::Color::Black);
        _text->setFillColor(sf::Color::White);
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            clicked = true;
            _click.play();
        }
    }
    return (clicked);
}

bool Button::isMouseHovering(const sf::RenderWindow &window) const
{
    return (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
}