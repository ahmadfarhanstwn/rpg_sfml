#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "EditorModes.h"

class State;
class GUI;
class PauseMenu;
class TileMap;
class EditorMode;
class DefaultEditorMode;

enum EDITORMODES
{
    DEFAULT_MODE = 0,
    ENEMY_MODE
};

class EditorState : public State
{
private:
    void initVariables();
    void initView();
    void initKeyBinds();
    void initFonts();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
    void initModes();
    void initEditorStatesData();

    //Variables
    sf::View view;
    float cameraSpeed;
    sf::Font font;
    PauseMenu* pMenu;
    EditorStateData editorStateData;

    std::map<std::string, gui::Buttons*> buttons;

    TileMap* tileMap;

    std::vector<EditorMode*> modes;

    unsigned activeMode;

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updateModes(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // EDITORSTATE_H
