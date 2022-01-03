#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include <EditorMode.h>

class EditorMode;
class StateData;
class State;
class TileMap;
class Tile;

class DefaultEditorMode : public EditorMode
{
private:
    int layer;
    sf::IntRect textureRect;
    sf::Text cursorText;
    bool collision;
    short type;
    bool tileAddLock;
    sf::RectangleShape selectorRect;
    sf::RectangleShape sidebar;
    gui::TextureSelector* textureSelector;

    void initVariables();
    void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif // DEFAULTMODE_H
