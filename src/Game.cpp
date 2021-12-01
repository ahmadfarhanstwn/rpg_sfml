#include "Game.h"

//Static Functions

//init variables
void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

//Init Functions
void Game::initWindow()
{
    /**initializing window stuff, set size, and the name of the window**/

    //read file display.ini
    std::ifstream ifs("Config/display.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    //initialize variable for init window
    std::string title = "None";
    sf::VideoMode window_size = sf::VideoMode::getDesktopMode();
    bool fullscreenMode = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    //change the variable to the setting in the config file
    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_size.width >> window_size.height;
        ifs >> fullscreenMode;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    //close the file
    ifs.close();

    //init window by the settings from init
    this->fullscreen = fullscreenMode;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_size, title, sf::Style::Fullscreen, this->windowSettings);
    else
        this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    //initialize keys from ini file
    std::ifstream ifs("Config/keyboards.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int value = 0;
        while (ifs >> key >> value)
        {
            this->supportedKeys[key] = value;
        }
    }
}

void Game::initStates()
{
    //push main menu state to the states stack, so it will be appeared first while open the app/game
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Constructor
Game::Game()
{
    //set all the init functions to the constructor
    this->initWindow();
    this->initKeys();
    this->initStates();
}

//Destructor
Game::~Game()
{
    //delete the window if it finished (to prevent the memory leaks)
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//Functions
void Game::endedApplication()
{
    std::cout << "Application Ended" << "\n";
}

void Game::updateDt()
{
    //Update the delta time with the time it takes to update and render
    this->dt = this->dtTime.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    //event stuff (close the window)
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::update()
{
    //updating all the functions
    this->updateSFMLEvents();

    if(!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endedApplication();
        this->window->close();
    }
}

void Game::render()
{
    //render all the stuff to window
    this->window->clear();

    //Render items
    if (!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    //run game
    while(this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
