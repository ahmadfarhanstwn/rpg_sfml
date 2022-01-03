#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "GUI.h"

class State;
class StateData;
class Tile;
class TileMap;

class EditorStateData
{
public:
    EditorStateData() {};

    float *keytime;
    float *keytimeMax;
    sf::View* view;
    sf::Font* font;
    std::map<std::string, int>* keybinds;
    sf::Vector2i *mousePosScreen;
    sf::Vector2i *mousePosWindow;
    sf::Vector2f *mousePosView;
    sf::Vector2i *mousePosGrid;
};

class EditorMode
{
protected:
    StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;

public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EditorMode();

    //Accessors
    const bool getKeytime();

    //Functions
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;

    virtual void renderGui(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif // EDITORMODE_H
