#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "GUI.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
    Player* player;

    sf::Font font;

    sf::VideoMode& vm;

    //Hp Bar
    std::string hpBarString;
    sf::Text hpBarText;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInside;

    //Exp Bar
    std::string expBarString;
    sf::Text expBarText;
    float expBarMaxWidth;
    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarInside;

    //Hp Bar
    std::string levelBarString;
    sf::Text levelBarText;
    float levelBarMaxWidth;
    sf::RectangleShape levelBarBack;

    void initFont();
    void initHpBar();
    void initExpBar();
    void initLevelBar();

public:
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();

    //Functions
    void updateHpBar();
    void updateExpBar();
    void updateLevelBar();
    void update(const float& dt);

    void renderHpBar(sf::RenderTarget& target);
    void renderExpBar(sf::RenderTarget& target);
    void renderLevelBar(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif // PLAYERGUI_H
