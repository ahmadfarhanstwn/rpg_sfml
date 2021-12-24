#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHpBar()
{
    float width = gui::p2pX(21.3f, vm);
    float height = gui::p2pY(6.5f, vm);
    this->hpBarMaxWidth = width;
    float x = gui::p2pX(1.4f, vm);
    float y = gui::p2pY(2.6f, vm);

    this->hpBarBack.setSize(sf::Vector2f(width,height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInside.setSize(sf::Vector2f(width,height));
    this->hpBarInside.setFillColor(sf::Color(250,20,20,200));
    this->hpBarInside.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setFont(this->font);
    this->hpBarText.setPosition(this->hpBarBack.getPosition().x + gui::p2pX(0.73f,vm),
                                this->hpBarBack.getPosition().y + gui::p2pY(0.65f,vm));
    this->hpBarText.setCharacterSize(gui::calcCharSize(vm, 90));
}

void PlayerGUI::initExpBar()
{
    float width = gui::p2pX(13.6f, vm);
    float height = gui::p2pY(3.9f, vm);
    this->expBarMaxWidth = width;
    float x = gui::p2pX(1.4f, vm);
    float y = gui::p2pY(11.f, vm);

    this->expBarBack.setSize(sf::Vector2f(width,height));
    this->expBarBack.setFillColor(sf::Color(50,50,50,200));
    this->expBarBack.setPosition(x, y);

    this->expBarInside.setSize(sf::Vector2f(width,height));
    this->expBarInside.setFillColor(sf::Color(20,250,20,200));
    this->expBarInside.setPosition(this->expBarBack.getPosition());

    this->expBarText.setFont(this->font);
    this->expBarText.setPosition(this->expBarBack.getPosition().x + gui::p2pX(0.73f,vm),
                                 this->expBarBack.getPosition().y + gui::p2pY(0.65f,vm));
    this->expBarText.setCharacterSize(gui::calcCharSize(vm,90));
}

void PlayerGUI::initLevelBar()
{
    float width = gui::p2pX(2.1f, vm);
    float height = gui::p2pY(3.9f, vm);
    this->levelBarMaxWidth = width;
    float x = gui::p2pX(1.4f, vm);
    float y = gui::p2pY(15.6f, vm);

    this->levelBarBack.setSize(sf::Vector2f(width,height));
    this->levelBarBack.setFillColor(sf::Color(50,50,50,200));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setPosition(this->levelBarBack.getPosition().x + gui::p2pX(0.73f,vm),
                                   this->levelBarBack.getPosition().y + gui::p2pY(0.65f,vm));
    this->levelBarText.setCharacterSize(gui::calcCharSize(vm, 90));
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm)
{
    this->player = player;

    this->initFont();
    this->initHpBar();
    this->initExpBar();
    this->initLevelBar();
}

PlayerGUI::~PlayerGUI()
{
    //dtor
}

//Functions
void PlayerGUI::updateHpBar()
{
    float percentage = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

    this->hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percentage)),
                                                                         this->hpBarInside.getSize().y));

    this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);

    this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updateExpBar()
{
    float percentage = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

    this->expBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(this->expBarMaxWidth * percentage)),
                                                                         this->expBarInside.getSize().y));

    this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);

    this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateLevelBar()
{
    this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);

    this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::update(const float& dt)
{
    this->updateHpBar();
    this->updateExpBar();
    this->updateLevelBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInside);
    target.draw(this->hpBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
    target.draw(this->expBarBack);
    target.draw(this->expBarInside);
    target.draw(this->expBarText);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
    target.draw(this->levelBarBack);
    target.draw(this->levelBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
    this->renderHpBar(target);
    this->renderExpBar(target);
    this->renderLevelBar(target);
}
