#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

class Entity;

class Player : public Entity
{
private:
    bool attacking;
    //init functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessor
    AttributeComponent* getAttributeComponent();

    //Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

#endif // PLAYER_H
