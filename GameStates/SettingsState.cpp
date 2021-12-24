#include "stdafx.h"
#include "SettingsState.h"

//Init Functions
void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initKeyBinds()
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

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULDN'T LOAD FONT(Dosis-Light.ttf)");
    }
}

void SettingsState::initGui()
{
    sf::VideoMode& vm = this->stateData->graphicsSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),
                                          static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw("ERROR::MAINMENUSTATE::BACKGROUNDTEXTURE::COULDN'T LOAD BACKGROUND FILE (bg1.png)");
    }

    this->background.setTexture(&this->backgroundTexture);

    this->buttons["BACK"] = new gui::Buttons(gui::p2pX(84.1f, vm),gui::p2pY(84.6, vm),gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm),
                                        &this->font,"Back", 30,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["APPLY"] = new gui::Buttons(gui::p2pX(69.5f, vm),gui::p2pY(84.6, vm),gui::p2pX(18.3f, vm),gui::p2pY(3.2f, vm),
                                        &this->font,"Apply", 30,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    std::vector<std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(gui::p2pX(47.5f, vm),gui::p2pY(45.5f, vm),gui::p2pX(14.6f, vm),gui::p2pY(6.5f, vm),font,modes_str.data(),modes_str.size(),0);

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(gui::p2pX(7.3f,vm),gui::p2pY(45.5f, vm)));
    this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
    this->optionsText.setFillColor(sf::Color(255,255,255,200));

    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

void SettingsState::resetGui()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->buttons.clear();

    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
    this->dropDownLists.clear();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initKeyBinds();
    this->initGui();
}

SettingsState::~SettingsState()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
    {
        delete it->second;
    }

    for (auto it2 = this->dropDownLists.begin(); it2 != dropDownLists.end(); it2++)
    {
        delete it2->second;
    }
}

void SettingsState::updateInput(const float& dt)
{
//    this->checkForQuit();
}

void SettingsState::updateGui(const float& dt)
{
    /**CHECK UPDATE FOR ALL BUTTONS AND CHECK IF A BUTTON IS PRESSED**/

    //Buttons
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }

    //Buttons Functionality

    //Drop Downs
    for(auto &it2 : this->dropDownLists)
    {
        it2.second->update(this->mousePosWindow, dt);
    }

    //Drop Downs funtionality

    //Quit the game
    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

    //Apply Settings
    if (this->buttons["APPLY"]->isPressed())
    {
        this->stateData->graphicsSettings->resolution = this->modes[this->dropDownLists["RESOLUTIONS"]->getActiveElementId()];
        this->window->create(this->stateData->graphicsSettings->resolution, this->stateData->graphicsSettings->title, sf::Style::Default);

        this->resetGui();
    }
}

void SettingsState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }

    for(auto &it2 : this->dropDownLists)
    {
        it2.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionsText);
}
