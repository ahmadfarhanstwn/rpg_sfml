#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font) : font(font)
{
    //background
    this->background.setSize(
                             sf::Vector2f(
                                          static_cast<float>(vm.width),
                                          static_cast<float>(vm.height))
                             );
    this->background.setFillColor(sf::Color(20,20,20,100));

    //container
    this->container.setSize(
                            sf::Vector2f(
                                          static_cast<float>(vm.width)/4.f,
                                          static_cast<float>(vm.height)-gui::p2pY(13.f,vm))
                            );
    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(
                                static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
                                30.f
                                );

    //init text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255,255,255,200));
    this->menuText.setCharacterSize(gui::calcCharSize(vm));
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
                               this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
                               this->container.getPosition().y + gui::p2pY(5.2f,vm));
}

PauseMenu::~PauseMenu()
{
    for (auto it = this->buttons.begin(); it != buttons.end(); it++)
        delete it->second;
}

/** ACCESSORS **/
std::map<std::string, gui::Buttons*>& PauseMenu::getButtons()
{
    return this->buttons;
}

const bool PauseMenu::isPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

/** FUNCTIONS **/
void PauseMenu::addButtons(std::string key, float y, const float width, const float height,
                           const unsigned char_size,const std::string text)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new gui::Buttons(x,y,width,height,
                                    &this->font,text, 30,
                                    sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                    sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0));
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
    for(auto &i : this->buttons)
    {
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(this->background);
    target.draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->menuText);
}
