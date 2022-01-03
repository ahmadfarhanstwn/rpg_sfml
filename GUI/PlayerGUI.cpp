#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHpBar()
{
    this->hpBar = new gui::ProgressBar(1.4f, 2.6f, 21.3f, 6.5f, this->player->getAttributeComponent()->hpMax,
                                       sf::Color::Red, 90, this->vm, &this->font);
}

void PlayerGUI::initExpBar()
{
    this->expBar = new gui::ProgressBar(1.4f, 11.1f, 13.6f, 3.9f, this->player->getAttributeComponent()->expNext,
                                        sf::Color::Blue, 150, this->vm, &this->font);
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
    delete this->hpBar;
    delete this->expBar;
}

//Functions
void PlayerGUI::updateHpBar()
{
    this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::updateExpBar()
{
    this->expBar->update(this->player->getAttributeComponent()->exp);
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
    this->hpBar->render(target);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
    this->expBar->render(target);
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
