#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
    //Variables
    GraphicsSettings graphicsSettings;
    StateData stateData;
    sf::RenderWindow* window;
    sf::Event ev;
    float gridSize;

    //Delta Time
    sf::Clock dtTime;
    float dt;

    //Keyboards
    std::map<std::string, int> supportedKeys;

    //States
    std::stack<State*> states;

    //Init Functions()
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();

public:
    //Constructor & Destructor
    Game();
    virtual ~Game();

    //Functions
    void endedApplication();
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif // GAME_H
