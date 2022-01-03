#include "stdafx.h"
#include "EditorState.h"

//Init Functions
void EditorState::initVariables()
{
    this->cameraSpeed = 1000.f;
}

void EditorState::initView()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->stateData->graphicsSettings->resolution.width),
                                    static_cast<float>(this->stateData->graphicsSettings->resolution.height)));
    this->view.setCenter(static_cast<float>(this->stateData->graphicsSettings->resolution.width)/2.f,
                         static_cast<float>(this->stateData->graphicsSettings->resolution.height)/2.f);
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
    sf::VideoMode& vm = this->stateData->graphicsSettings->resolution;

    this->pMenu = new PauseMenu(this->stateData->graphicsSettings->resolution, this->font);

    this->pMenu->addButtons("SAVE", gui::p2pY(19.5f, vm), gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm), gui::calcCharSize(vm), "Save Map");
    this->pMenu->addButtons("LOAD", gui::p2pY(29.2f, vm), gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm), gui::calcCharSize(vm), "Load Map");
    this->pMenu->addButtons("QUIT", gui::p2pY(39.f, vm), gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm), gui::calcCharSize(vm), "Exit Map");
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{

}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 100,100, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
    this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
    this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

    this->activeMode = EDITORMODES::DEFAULT_MODE;
}

void EditorState::initEditorStatesData()
{
    this->editorStateData.view = &this->view;
    this->editorStateData.keytime = &this->keytime;
    this->editorStateData.keytimeMax = &this->keytimeMax;
    this->editorStateData.keybinds = &this->keyBinds;
    this->editorStateData.font = &this->font;
    this->editorStateData.mousePosGrid = &this->mousePosGrid;
    this->editorStateData.mousePosScreen = &this->mousePosScreen;
    this->editorStateData.mousePosView = &this->mousePosView;
    this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

EditorState::EditorState(StateData* state_data) :
    State(state_data)
{
    this->initVariables();
    this->initEditorStatesData();
    this->initView();
    this->initFonts();
    this->initKeyBinds();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();
    this->initGui();
    this->initModes();
}

EditorState::~EditorState()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
        delete it->second;
    delete this->pMenu;
    delete this->tileMap;

    for (size_t i = 0; i < this->modes.size(); i++)
        delete this->modes[i];
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
    //Move Camera
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Move_Camera_Up"))))
    {
        this->view.move(0, -this->cameraSpeed*dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Move_Camera_Down"))))
    {
        this->view.move(0, this->cameraSpeed*dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Move_Camera_Left"))))
    {
        this->view.move(-this->cameraSpeed*dt, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Move_Camera_Right"))))
    {
        this->view.move(this->cameraSpeed*dt, 0);
    }

    //Change Mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Mode_Up"))))
    {
        if (this->activeMode < this->modes.size()-1) this->activeMode++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Mode_Down"))))
    {
        if (this->activeMode > 0) this->activeMode--;
    }
}

void EditorState::updateButtons()
{
    /**CHECK UPDATE FOR ALL BUTTONS AND CHECK IF A BUTTON IS PRESSED**/
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::updateGui(const float& dt)
{

}

void EditorState::updateModes(const float& dt)
{
    this->modes[this->activeMode]->update(dt);
}

void EditorState::updatePauseMenuButtons()
{
    if (this->pMenu->isPressed("SAVE") && this->getKeytime())
    {
        this->tileMap->saveToFile("test.slmp");
    }
    if (this->pMenu->isPressed("LOAD") && this->getKeytime())
    {
        this->tileMap->loadFromFile("test.slmp");
    }
    if (this->pMenu->isPressed("QUIT") && this->getKeytime())
    {
        this->endState();
    }
}

void EditorState::update(const float& dt)
{
    this->updateMousePosition(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused) //unpaused
    {
        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
        this->updateModes(dt);
    }
    else //paused
    {
        this->pMenu->update(this->mousePosWindow);
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

}

void EditorState::renderModes(sf::RenderTarget& target)
{
    this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->setView(this->view);
    this->tileMap->render(*target, this->mousePosGrid, nullptr, sf::Vector2f(),true);
    this->tileMap->renderDeferred(*target);

    target->setView(this->view);
    this->renderButtons(*target);
    this->renderGui(*target);
    this->renderModes(*target);

    //render pause menu
    if (this->paused)
    {
        target->setView(this->window->getDefaultView());
        this->pMenu->render(*target);
    }
}
