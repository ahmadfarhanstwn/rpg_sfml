#include "stdafx.h"
#include "MainMenuState.h"

//Init Functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initKeyBinds()
{
    std::ifstream ifs("Config/mainmenukeybinds.ini");

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

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULDN'T LOAD FONT(Dosis-Light.ttf)");
    }
}

void MainMenuState::initGui()
{
    sf::VideoMode& vm = this->stateData->graphicsSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),
                                          static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png"))
    {
        throw("ERROR::MAINMENUSTATE::BACKGROUNDTEXTURE::COULDN'T LOAD BACKGROUND FILE (bg1.png)");
    }

    this->background.setTexture(&this->backgroundTexture);

    this->buttons["GAME_STATE"] = new gui::Buttons(gui::p2pX(11.f, vm),gui::p2pY(39.1f, vm),
                                                   gui::p2pX(29.2f, vm),gui::p2pY(6.5f, vm),
                                              &this->font,"New Game", gui::calcCharSize(vm),
                                              sf::Color(200,200,200,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["SETTINGS_STATE"] = new gui::Buttons(gui::p2pX(11.f, vm),gui::p2pY(48.3f, vm),
                                                       gui::p2pX(29.2f, vm),gui::p2pY(6.5f, vm),
                                            &this->font,"Settings", gui::calcCharSize(vm),
                                            sf::Color(200,200,200,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["EDIT_STATE"] = new gui::Buttons(gui::p2pX(11.f, vm),gui::p2pY(57.4f, vm),gui::p2pX(29.2f, vm),gui::p2pY(6.5f, vm),
                                              &this->font,"Editor", gui::calcCharSize(vm),
                                              sf::Color(200,200,200,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["QUIT"] = new gui::Buttons(gui::p2pX(11.f, vm),gui::p2pY(66.5f, vm),gui::p2pX(29.2f, vm),gui::p2pY(6.5f, vm),
                                        &this->font,"Quit", gui::calcCharSize(vm),
                                        sf::Color(200,200,200,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));
}

void MainMenuState::resetGui()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
        delete it->second;

    this->buttons.clear();
    this->initGui();
}

MainMenuState::MainMenuState(StateData* state_data) :
    State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initKeyBinds();
    this->initGui();
}

MainMenuState::~MainMenuState()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
        delete it->second;
}

void MainMenuState::updateInput(const float& dt)
{
//    this->checkForQuit();
}

void MainMenuState::updateButtons()
{
    /**CHECK UPDATE FOR ALL BUTTONS AND CHECK IF A BUTTON IS PRESSED**/
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }

    //New Game
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->stateData));
    }

    //Settings
    if (this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingsState(this->stateData));
    }

    //Editor
    if (this->buttons["EDIT_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->stateData));
    }

    //Quit the game
    if (this->buttons["QUIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(*target);
}
