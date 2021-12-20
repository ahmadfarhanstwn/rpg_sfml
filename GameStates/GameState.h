#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class PauseMenu;
class Player;
class TileMap;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pMenu;
    Player* player;
    PlayerGUI* playerGui;

    TileMap* tileMap;

    void initDeferredRender();
    void initView();
    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initPlayerGui();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateTileMap(const float & dt);
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void updatePlayerGui(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif // GAMESTATE_H
