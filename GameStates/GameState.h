#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Enemies_Include.h"

class PauseMenu;
class Player;
class TileMap;
class PlayerGUI;
class Sword;
class Enemy;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    sf::Shader coreShader;

    sf::Font font;
    PauseMenu* pMenu;
    Player* player;
    PlayerGUI* playerGui;

    TileMap* tileMap;

    std::vector<Enemy*> activeEnemies;

    void initDeferredRender();
    void initView();
    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initShader();
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
