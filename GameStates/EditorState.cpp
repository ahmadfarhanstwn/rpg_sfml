#include "stdafx.h"
#include "EditorState.h"

//Init Functions
void EditorState::initVariables()
{

}

void EditorState::initBackgrounds()
{

}

void EditorState::initKeyBinds()
{
    std::ifstream ifs("Config/editorkeybinds.ini");

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

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULDN'T LOAD FONT(Dosis-Light.ttf)");
    }
}

void EditorState::initPauseMenu()
{
    this->pMenu = new PauseMenu(*this->window, this->font);

    this->pMenu->addButtons("QUIT", 150.f, "Exit Game");
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 10,10);
}

EditorState::EditorState(StateData* state_data) :
    State(state_data)
{
    this->initVariables();
    this->initBackgrounds();
    this->initFonts();
    this->initKeyBinds();
    this->initPauseMenu();
    this->initButtons();
    this->initGui();
    this->initTileMap();
}

EditorState::~EditorState()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
        delete it->second;
    delete this->pMenu;
    delete this->tileMap;
}

void EditorState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Escape"))) && this->getKeytime())
    {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void EditorState::updateEditorInput(const float& dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
    {
        this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
}

void EditorState::updateButtons()
{
    /**CHECK UPDATE FOR ALL BUTTONS AND CHECK IF A BUTTON IS PRESSED**/
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::updateGui()
{
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,
                                   this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePauseMenuButtons()
{
    if (this->pMenu->isPressed("QUIT") && this->getKeytime())
    {
        this->endState();
    }
}

void EditorState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused) //unpaused
    {
        this->updateButtons();
        this->updateGui();
        this->updateEditorInput(dt);
    }
    else //paused
    {
        this->pMenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget& target)
{
    target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->renderButtons(*target);
    this->renderGui(*target);

    this->tileMap->render(*target);

    //render pause menu
    if (this->paused)
    {
        this->pMenu->render(*target);
    }
}
