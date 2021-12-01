#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    //entity component
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;

    float movementSpeed;

public:
    Entity();
    virtual ~Entity();

    //Functions
    void setPosition(const float x, const float y);
    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);
};

#endif // ENTITY_H
