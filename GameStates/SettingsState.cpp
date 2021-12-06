#include "SettingsState.h"

//Init Functions
void SettingsState::initVariables()
{

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
    this->buttons["QUIT"] = new gui::Buttons(0,0,250,25,
                                        &this->font,"Back", 20,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    std::string resolutionLists[] = {"1366x768", "800x600", "640x480"};
    this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(650,350,200,50,font,resolutionLists,3,0);
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackgrounds();
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
        it.second->update(this->mousePosView);
    }

    //Buttons Functionality

    //Drop Downs
    for(auto &it2 : this->dropDownLists)
    {
        it2.second->update(this->mousePosView, dt);
    }

    //Drop Downs funtionality

    //Quit the game
    if (this->buttons["QUIT"]->isPressed())
    {
        this->endState();
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
}
