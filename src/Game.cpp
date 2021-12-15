#include "stdafx.h"
#include "Game.h"

//Static Functions

//init variables
void Game::initVariables()
{
    this->window = NULL;
//    this->fullscreen = false;
    this->dt = 0.f;

    this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
    this->graphicsSettings.loadFromFile("Config/graphics.ini");
}

//Init Functions
void Game::initWindow()
{
    if (this->graphicsSettings.fullscreen)
        this->window = new sf::RenderWindow(
                                            this->graphicsSettings.resolution,
                                            this->graphicsSettings.title,
                                            sf::Style::Fullscreen,
                                            this->graphicsSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
                                            this->graphicsSettings.resolution,
                                            this->graphicsSettings.title,
                                            sf::Style::Titlebar | sf::Style::Close,
                                            this->graphicsSettings.contextSettings);
    this->window->setFramerateLimit(this->graphicsSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicsSettings.verticalSync);
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

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.graphicsSettings = &this->graphicsSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
    //push main menu state to the states stack, so it will be appeared first while open the app/game
    this->states.push(new MainMenuState(&this->stateData));
}

//Constructor
Game::Game()
{
    //set all the init functions to the constructor
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
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
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if(this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
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
