#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHpBar()
{
    float width = 300.f;
    float height = 50.f;
    this->hpBarMaxWidth = width;
    float x = 20.f;
    float y = 20.f;

    this->hpBarBack.setSize(sf::Vector2f(width,height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInside.setSize(sf::Vector2f(width,height));
    this->hpBarInside.setFillColor(sf::Color(250,20,20,200));
    this->hpBarInside.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setFont(this->font);
    this->hpBarText.setPosition(this->hpBarBack.getPosition().x + 10.f, this->hpBarBack.getPosition().y + 5.f);
}

void PlayerGUI::initExpBar()
{
    float width = 200.f;
    float height = 30.f;
    this->expBarMaxWidth = width;
    float x = 20.f;
    float y = 85.f;

    this->expBarBack.setSize(sf::Vector2f(width,height));
    this->expBarBack.setFillColor(sf::Color(50,50,50,200));
    this->expBarBack.setPosition(x, y);

    this->expBarInside.setSize(sf::Vector2f(width,height));
    this->expBarInside.setFillColor(sf::Color(20,250,20,200));
    this->expBarInside.setPosition(this->expBarBack.getPosition());

    this->expBarText.setFont(this->font);
    this->expBarText.setPosition(this->expBarBack.getPosition().x + 10.f, this->expBarBack.getPosition().y + 5.f);
    this->expBarText.setCharacterSize(12);
}

void PlayerGUI::initLevelBar()
{
    float width = 30.f;
    float height = 30.f;
    this->levelBarMaxWidth = width;
    float x = 20.f;
    float y = 120.f;

    this->levelBarBack.setSize(sf::Vector2f(width,height));
    this->levelBarBack.setFillColor(sf::Color(50,50,50,200));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setPosition(this->levelBarBack.getPosition().x + 10.f, this->levelBarBack.getPosition().y + 5.f);
    this->levelBarText.setCharacterSize(12);
}

PlayerGUI::PlayerGUI(Player* player)
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
