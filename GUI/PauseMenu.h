#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GUI.h"

class Gui;

class PauseMenu
{
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string, gui::Buttons*> buttons;

public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Accessors
    std::map<std::string, gui::Buttons*>& getButtons();
    const bool   isPressed(const std::string key);

    //Functions
    void addButtons(std::string key, float y, const std::string text);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
};

#endif // PAUSEMENU_H
