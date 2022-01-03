#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class MovementComponent;
class AnimationComponent;
class HitboxComponent;
class AttributeComponent;
class SkillComponent;

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
    AttributeComponent* attributeComponent;
    SkillComponent* skillComponent;

    float movementSpeed;

public:
    Entity();
    virtual ~Entity();

    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2f getCenter() const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

    //Functions
    virtual void setPosition(const float x, const float y);
    void setTexture(sf::Texture& texture);

    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createAttributeComponent(const unsigned level);
    void createSkillComponent();

    //Stop Velocity
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool showHitbox) = 0;
};

#endif // ENTITY_H
