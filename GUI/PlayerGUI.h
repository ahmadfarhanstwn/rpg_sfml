#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
    Player* player;

    sf::Font font;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInside;

    void initFont();
    void initHpBar();

public:
    PlayerGUI(Player* player);
    virtual ~PlayerGUI();

    //Functions
    void updateHpBar();
    void update(const float& dt);

    void renderHpBar(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif // PLAYERGUI_H
