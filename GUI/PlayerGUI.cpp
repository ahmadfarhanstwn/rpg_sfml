#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHpBar()
{
    float width = 300.f;
    float height = 50.f;
    float x = 20.f;
    float y = 20.f;

    this->hpBarBack.setSize(sf::Vector2f(width,height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInside.setSize(sf::Vector2f(width,height));
    this->hpBarInside.setFillColor(sf::Color(250,20,20,200));
    this->hpBarInside.setPosition(this->hpBarBack.getPosition());
}

PlayerGUI::PlayerGUI(Player* player)
{
    this->player = player;

    this->initFont();
    this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{
    //dtor
}

//Functions
void PlayerGUI::updateHpBar()
{

}

void PlayerGUI::update(const float& dt)
{

}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInside);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
    this->renderHpBar(target);
}
