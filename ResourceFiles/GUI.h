#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <vector>

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

namespace gui
{
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
        const std::string getText() const;

        //Modifier
        void setText(const std::string text);

        //Function
        void update(const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);
    };

    class DropDownList
    {
    private:
        sf::Font& font;
        gui::Buttons* activeElement;
        std::vector<gui::Buttons*> list;
        bool showList;
        float keytime;
        float keytimeMax;

    public:
        DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index);
        ~DropDownList();

        //Accessors
        const bool getKeytime();

        //Function
        void updateKeytime(const float& dt);
        void update(const sf::Vector2f& mousePos, const float& dt);
        void render(sf::RenderTarget& target);
    };
}

#endif // BUTTONS_H
