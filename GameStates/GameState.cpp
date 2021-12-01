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

void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
        throw("ERROR::GAMESTATE::INITTEXTURES::COULDN'T LOAD TEXTURE FILE (PLAYER_SHEET.png)");
}

void GameState::initPlayers()
{
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
    State(window, supportedKeys, states)
{
    this->initTextures();
    this->initPlayers();
    this->initKeyBinds();
}

GameState::~GameState()
{
    delete this->player;
}

void GameState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);

    //exit the state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Escape"))))
        this->endState();
}

void GameState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->player->render(target);
}
