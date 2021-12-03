#ifndef BUTTONS_H
#define BUTTONS_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_states
{
    BTN_IDLE,
    BTN_HOVERED,
    BTN_ACTIVE
};

class Buttons
{
private:
    short unsigned btnState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Buttons(float x, float y, float width, float height, sf::Font* font, std::string text,
            unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
    virtual ~Buttons();

    //Accessors
    const bool isPressed() const;

    //Function
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
};

#endif // BUTTONS_H
