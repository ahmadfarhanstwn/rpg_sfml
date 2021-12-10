#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

class EditorState : public State
{
private:
    void initVariables();
    void initBackgrounds();
    void initKeyBinds();
    void initFonts();
    void initText();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

    sf::Font font;
    sf::IntRect textureRect;
    sf::Text cursorText;
    PauseMenu* pMenu;
    TileMap* tileMap;

    sf::RectangleShape selectorRect;
    sf::RectangleShape sidebar;

    std::map<std::string, gui::Buttons*> buttons;
    gui::TextureSelector* textureSelector;

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // EDITORSTATE_H
