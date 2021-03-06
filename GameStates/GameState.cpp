#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
    this->renderTexture.create(this->stateData->graphicsSettings->resolution.width,
                               this->stateData->graphicsSettings->resolution.height);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0,0,
                                                  this->stateData->graphicsSettings->resolution.width,
                                                  this->stateData->graphicsSettings->resolution.height));
}

void GameState::initView()
{
    this->view.setSize(sf::Vector2f(this->stateData->graphicsSettings->resolution.width,
                                    this->stateData->graphicsSettings->resolution.height));

    this->view.setCenter(sf::Vector2f(this->stateData->graphicsSettings->resolution.width / 2.f,
                                      this->stateData->graphicsSettings->resolution.height / 2.f));
}

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
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png"))
        throw("ERROR::GAMESTATE::INITTEXTURES::COULDN'T LOAD TEXTURE FILE (PLAYER_SHEET.png)");

    if(!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
        throw("ERROR::GAMESTATE::INITTEXTURES::COULDN'T LOAD TEXTURE FILE (rat1_60x64.png)");
}

void GameState::initPauseMenu()
{
    sf::VideoMode& vm = this->stateData->graphicsSettings->resolution;

    this->pMenu = new PauseMenu(this->stateData->graphicsSettings->resolution, this->font);

    this->pMenu->addButtons("QUIT", gui::p2pY(19.5f, vm), gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm), gui::calcCharSize(vm),"Exit Game");
}

void GameState::initShader()
{
    if(!this->coreShader.loadFromFile("ResourceFiles/vertex_shader.vert", "ResourceFiles/fragment_shader.frag"))
    {
        std::cout << "ERROR::GameState::InitShader::Couldn't Load Shader" << "\n";
    };/////
}

void GameState::initPlayers()
{
    this->player = new Player(250,250, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGui()
{
    this->playerGui = new PlayerGUI(this->player, this->stateData->graphicsSettings->resolution);
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap("test.slmp");
}

GameState::GameState(StateData* state_data) :
    State(state_data)
{
    this->initDeferredRender();
    this->initView();
    this->initKeyBinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initShader();
    this->initPlayers();
    this->initPlayerGui();
    this->initTileMap();

    this->activeEnemies.push_back(new Rat(200.f, 100.f, this->textures["RAT1_SHEET"]));
    this->activeEnemies.push_back(new Rat(300.f, 600.f, this->textures["RAT1_SHEET"]));
    this->activeEnemies.push_back(new Rat(500.f, 300.f, this->textures["RAT1_SHEET"]));
    this->activeEnemies.push_back(new Rat(900.f, 100.f, this->textures["RAT1_SHEET"]));
    this->activeEnemies.push_back(new Rat(750.f, 800.f, this->textures["RAT1_SHEET"]));
}

GameState::~GameState()
{
    delete this->pMenu;
    delete this->player;
    delete this->tileMap;
    delete this->playerGui;

    for (size_t i = 0; i < this->activeEnemies.size(); i++)
    {
        delete this->activeEnemies[i];
    }
}

//Functions
void GameState::updateTileMap(const float& dt)
{
    this->tileMap->update(this->player, dt);

    for (auto *i : this->activeEnemies)
    {
        this->tileMap->update(i, dt);
    }
}

void GameState::updateView(const float& dt)
{
    this->view.setCenter(std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->graphicsSettings->resolution.width / 2)) / 5.f),
                         std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->graphicsSettings->resolution.height / 2)) / 5.f));

    if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
    {
        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
        {
            this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
    }

    if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
    {
        if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
        {
            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
        }
        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
        {
            this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
        }
    }

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
    this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
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
    {
        this->player->move(0.f, -1.f, dt);
        if(this->getKeytime())
            this->player->gainExp(1000);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, dt);
        if(this->getKeytime())
            this->player->loseExp(10);
    }
}

void GameState::updatePauseMenuButtons()
{
    if (this->pMenu->isPressed("QUIT") && this->getKeytime())
    {
        this->endState();
    }
}

void GameState::updatePlayerGui(const float& dt)
{

}

void GameState::update(const float& dt)
{
    this->updateMousePosition(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused) //not paused
    {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->updateTileMap(dt);
        this->player->update(dt, this->mousePosView);
        this->playerGui->update(dt);
        for (auto *i : this->activeEnemies)
        {
            i->update(dt, this->mousePosView);
        }
    }
    else //paused
    {
        this->pMenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->renderTexture.clear();

    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture,
                          this->viewGridPosition,
                          &this->coreShader,
                          this->player->getCenter(),
                          false);

    for (auto *i : this->activeEnemies)
    {
        i->render(this->renderTexture, &this->coreShader, this->player->getCenter(), false);
    }

    this->player->render(this->renderTexture, &this->coreShader, this->player->getCenter(), false);

    this->tileMap->renderDeferred(this->renderTexture,
                                  &this->coreShader,
                                  this->player->getCenter());

    this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->playerGui->render(this->renderTexture);

    //render pause menu
    if (this->paused)
    {
//        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pMenu->render(this->renderTexture);
    }

    //Final render
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}
