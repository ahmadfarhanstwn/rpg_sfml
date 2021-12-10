#include "stdafx.h"
#include "GameState.h"

void GameState::initKeyBinds()
{
    std::ifstream ifs("Config/keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string suppKey = "";
        while (ifs >> key >> suppKey)
        {
            this->keyBinds[key] = this->supportedKeys->at(suppKey);
        }
    }
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULDN'T LOAD FONT(Dosis-Light.ttf)");
    }
}

void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
        throw("ERROR::GAMESTATE::INITTEXTURES::COULDN'T LOAD TEXTURE FILE (PLAYER_SHEET.png)");
}

void GameState::initPauseMenu()
{
    this->pMenu = new PauseMenu(*this->window, this->font);

    this->pMenu->addButtons("QUIT", 150.f, "Exit Game");
}

void GameState::initPlayers()
{
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");
}

GameState::GameState(StateData* state_data) :
    State(state_data)
{
    this->initKeyBinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pMenu;
    delete this->player;
    delete this->tileMap;
}

void GameState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Escape"))) && this->getKeytime())
    {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void GameState::updatePlayerInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
}

void GameState::updatePauseMenuButtons()
{
    if (this->pMenu->isPressed("QUIT") && this->getKeytime())
    {
        this->endState();
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused) //not paused
    {
        this->updatePlayerInput(dt);
        this->player->update(dt);
    }
    else //paused
    {
        this->pMenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

//    this->map.render(*target);

    this->player->render(*target);

    //render pause menu
    if (this->paused)
    {
        this->pMenu->render(*target);
    }
}
