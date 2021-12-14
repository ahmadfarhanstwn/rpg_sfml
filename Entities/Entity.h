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

    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2u getGridPosition(const unsigned gridSizeU) const;

    //Functions
    virtual void setPosition(const float x, const float y);
    void setTexture(sf::Texture& texture);

    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

    //Stop Velocity
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif // ENTITY_H
