#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include "Sword.h"

class Entity;

class Player : public Entity
{
private:
    bool attacking;
    //init functions
    void initVariables();
    void initComponents();
    void initAnimations();

    Sword sword;

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessor
    AttributeComponent* getAttributeComponent();

    //Functions
    void loseHp(const int hp);
    void gainHp(const int hp);
    void loseExp(const unsigned exp);
    void gainExp(const unsigned exp);

    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool showHitbox = false);
};

#endif // PLAYER_H
