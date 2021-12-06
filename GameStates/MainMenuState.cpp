#include "MainMenuState.h"

//Init Functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackgrounds()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw("ERROR::MAINMENUSTATE::BACKGROUNDTEXTURE::COULDN'T LOAD BACKGROUND FILE (bg1.png)");
    }

    this->background.setTexture(&this->backgroundTexture);
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

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new gui::Buttons(150,300,400,50,
                                              &this->font,"New Game", 50,
                                              sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["SETTINGS_STATE"] = new gui::Buttons(150,370,400,50,
                                            &this->font,"Settings", 50,
                                            sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                            sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["EDIT_STATE"] = new gui::Buttons(150,440,400,50,
                                              &this->font,"Editor", 50,
                                              sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                              sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));

    this->buttons["QUIT"] = new gui::Buttons(150,510,400,50,
                                        &this->font,"Quit", 50,
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                        sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
    State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackgrounds();
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();
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
        it.second->update(this->mousePosView);
    }

    //New Game
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    //Settings
    if (this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
    }

    //Editor
    if (this->buttons["EDIT_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
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
