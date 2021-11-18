/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** InputBox
*/

#include "InputBox.hpp"

InputBox::InputBox()
{
}

InputBox::~InputBox()
{
}

void InputBox::create(const sf::Vector2f &size, const sf::Vector2f &pos, const std::string &title, const std::string &defaultInput, const bool &ip, const bool &num, const bool &alpha, const sf::Vector2f &factors)
{
    _background.setSize(sf::Vector2f(size.x, size.y));
    _background.setFillColor(sf::Color::Black);
    _background.setOutlineColor(sf::Color::White);
    _background.setOutlineThickness(2.0);
    _background.setPosition(sf::Vector2f(pos.x, pos.y));
    _background.setOrigin(sf::Vector2f(_background.getSize().x / 2, _background.getSize().y / 2));

    _font = AssetManager<sf::Font>::getAssetManager().getAsset("assets/fonts/OxygenMono-Regular.ttf");

    _title = title;
    _titleText.setString(_title);
    _titleText.setScale(factors);
    _titleText.setFont(_font);
    _titleText.setOrigin(sf::Vector2f(_titleText.getGlobalBounds().left + _titleText.getGlobalBounds().width / 2, _titleText.getGlobalBounds().top + _titleText.getGlobalBounds().height / 2));
    _titleText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 2 - _titleText.getGlobalBounds().height));

    _input = defaultInput;
    if (_input == "")
        _input = "INIT";
    _inputText.setString(_input);
    _inputText.setFont(_font);
    _inputText.setOrigin(sf::Vector2f(_inputText.getGlobalBounds().left + _inputText.getGlobalBounds().width / 2, _inputText.getGlobalBounds().top + _inputText.getGlobalBounds().height / 2));
    _inputText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));
    if (_input == "INIT") {
        _input = "";
        _inputText.setString(_input);
    }

    _cursor.setSize(sf::Vector2f(2.0, size.y / 1.4));
    _cursor.setFillColor(sf::Color::White);
    _cursor.setOrigin(sf::Vector2f(_cursor.getSize().x / 2, _cursor.getSize().y / 2));
    _cursor.setPosition(sf::Vector2f(_inputText.getGlobalBounds().left + _inputText.getGlobalBounds().width + 5, _inputText.getGlobalBounds().top + _inputText.getGlobalBounds().height / 2));
    _cursorClock.restart();

    _isFocus = false;

    _ip = ip;
    _num = num;
    _alpha = alpha;
}

void InputBox::setPosition(const sf::Vector2f &pos)
{
    _background.setPosition(pos);
    _titleText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y - _background.getSize().y / 2 - _titleText.getGlobalBounds().height));
    _inputText.setPosition(sf::Vector2f(_background.getPosition().x, _background.getPosition().y));
    _cursor.setPosition(sf::Vector2f(_inputText.getGlobalBounds().left + _inputText.getGlobalBounds().width + 5, _inputText.getGlobalBounds().top + _inputText.getGlobalBounds().height / 2));
}

void InputBox::update()
{
    if (_cursorClock.getElapsedTime().asSeconds() >= 0.8)
        _cursorClock.restart();
}

void InputBox::event(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            _isFocus = true;
        else
            _isFocus = false;
    }
    if (event.type == sf::Event::TextEntered && _isFocus == true) {
        if ((_alpha == true && ((event.text.unicode >= 'a' && event.text.unicode <= 'z')
        || (event.text.unicode >= 'A' && event.text.unicode <= 'Z')))
        || (_num == true && (event.text.unicode >= '0' && event.text.unicode <= '9'))
        || (_ip == true && event.text.unicode == '.')) {
            if (_input.size() > 15)
            return;
            _input += event.text.unicode;
        }
        if (event.text.unicode == 8 && _input.size() > 0)
            _input.pop_back();
        _inputText.setString(_input);
        _inputText.setOrigin(sf::Vector2f(_inputText.getGlobalBounds().width / 2, _inputText.getOrigin().y));
        _cursor.setPosition(sf::Vector2f(_inputText.getGlobalBounds().left + _inputText.getGlobalBounds().width + 5, _cursor.getPosition().y));
    }
    if (event.type == sf::Event::MouseMoved) {
        if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            _background.setOutlineColor(sf::Color::Yellow);
        }
        else {
            _background.setOutlineColor(sf::Color::White);
        }
    }
}

void InputBox::draw(sf::RenderWindow &window) const
{
    window.draw(_background);
    if (_isFocus == true && _cursorClock.getElapsedTime().asSeconds() >= 0.4)
        window.draw(_cursor);
    if (_titleText.getString() != "")
        window.draw(_titleText);
    if (_inputText.getString() != "")
        window.draw(_inputText);
}

std::string InputBox::getInputString() const
{
    return (_inputText.getString());
}