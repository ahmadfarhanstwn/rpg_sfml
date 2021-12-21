#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
    this->stateData = state_data;
    this->states = state_data->states;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->gridSize = state_data->gridSize;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 2.f;
}

State::~State()
{
    //dtor
}

/** ACCESSORS **/
const bool& State::getQuit() const
{
    return this->quit;
}

const bool State::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

/** FUNCTIONS **/
const float State::p2pX(const float perc)
{
    return std::floor(static_cast<float>(this->stateData->graphicsSettings->resolution->width) * (perc / 100.f));
}

const float State::p2pY(const float perc)
{
    return std::floor(static_cast<float>(this->stateData->graphicsSettings->resolution->height) * (perc / 100.f));
}

void State::updateMousePosition(sf::View* view)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    if (view)
        this->window->setView(*view);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePosGrid = sf::Vector2i(static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
                                      static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize));
    this->window->setView(this->window->getDefaultView());
}

void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}

void State::updateKeytime(const float& dt)
{
    if(this->keytime < this->keytimeMax)
    {
        this->keytime += 10.f * dt;
    }
}
