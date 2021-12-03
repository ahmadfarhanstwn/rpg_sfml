#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
private:

protected:
    sf::RenderWindow* window;
    std::map<std::string,int>* supportedKeys;
    std::stack<State*>* states;
    std::map<std::string,int> keyBinds;

    //Positions
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    std::map<std::string, sf::Texture> textures;
    bool quit;
    bool paused;

    virtual void initKeyBinds() = 0;

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    //Accessor
    const bool& getQuit() const;

    //Function
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePosition();
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt)=0;
    virtual void render(sf::RenderTarget* target = nullptr)=0;
};

#endif // STATE_H
