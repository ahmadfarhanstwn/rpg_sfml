#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <GameState.h>
#include "EditorState.h"
#include "SettingsState.h"
#include "GUI.h"
#include "GraphicsSettings.h"

class MainMenuState : public State
{
private:
    void initVariables();
    void initBackgrounds();
    void initKeyBinds();
    void initFonts();
    void initButtons();

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Buttons*> buttons;

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& dt);

    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // MAINMENUSTATE_H
