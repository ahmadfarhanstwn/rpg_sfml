#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <string>

#include "Buttons.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class PauseMenu
{
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string, Buttons*> buttons;

public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Functions
    void update();
    void render(sf::RenderTarget& target);
};

#endif // PAUSEMENU_H
