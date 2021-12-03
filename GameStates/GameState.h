#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"


class GameState : public State
{
private:
    sf::Font font;
    PauseMenu* pMenu;
    Player* player;

    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);

    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif // GAMESTATE_H
