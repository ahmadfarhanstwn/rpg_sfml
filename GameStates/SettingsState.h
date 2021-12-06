#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <State.h>
#include "GUI.h"

class SettingsState : public State
{
private:
    void initVariables();
    void initBackgrounds();
    void initKeyBinds();
    void initFonts();
    void initGui();

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Buttons*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Functions
    void updateInput(const float& dt);

    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // SETTINGSSTATE_H
