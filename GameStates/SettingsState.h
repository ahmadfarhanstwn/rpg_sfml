#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <State.h>
#include "GUI.h"
#include "GraphicsSettings.h"

class SettingsState : public State
{
private:
    void initVariables();
    void initBackgrounds();
    void initKeyBinds();
    void initFonts();
    void initGui();
    void initText();

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text optionsText;

    std::map<std::string, gui::Buttons*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;
    std::vector<sf::VideoMode> modes;

public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Functions
    void updateInput(const float& dt);

    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // SETTINGSSTATE_H
