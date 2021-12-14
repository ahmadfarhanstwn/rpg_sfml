#include "stdafx.h"
#include "SettingsState.h"

//Init Functions
void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackgrounds()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw("ERROR::MAINMENUSTATE::BACKGROUNDTEXTURE::COULDN'T LOAD BACKGROUND FILE (bg1.png)");
    }

    this->background.setTexture(&this->backgroundTexture);
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
    this->buttons["BACK"] = new gui::Buttons(1150,650,250,25,
                                        &this->font,"Back", 30,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["APPLY"] = new gui::Buttons(950,650,250,25,
                                        &this->font,"Apply", 30,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));



    std::vector<std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(650,350,200,50,font,modes_str.data(),modes_str.size(),0);
}

void SettingsState::initText()
{
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(100.f,350.f));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color(255,255,255,200));

    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    this->initVariables();
    this->initBackgrounds();
    this->initFonts();
    this->initKeyBinds();
    this->initGui();
    this->initText();
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
