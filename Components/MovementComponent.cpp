#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration) :
    sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
    //dtor
}

/** Accessors **/
const float& MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
    switch(state)
    {
    case IDLE:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f)
            return true;
        break;
    case MOVING:
        if (this->velocity.x != 0.f || this->velocity.y != 0.f)
            return true;
        break;
    case MOVING_LEFT:
        if (this->velocity.x < 0.f)
            return true;
        break;
    case MOVING_RIGHT:
        if (this->velocity.x > 0.f)
            return true;
        break;
    case MOVING_UP:
        if (this->velocity.y < 0.f)
            return true;
        break;
    case MOVING_DOWN:
        if (this->velocity.y > 0.f)
            return true;
        break;
    }
    return false;
}

/** Functions **/
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    //Accelerating
    this->velocity.x += this->acceleration * dir_x;

    this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
    if (this->velocity.x > 0.f) // check for the positive x
    {
        //Check for the maximum velocity
        if (this->velocity.x > this->maxVelocity)
        {
            this->velocity.x = this->maxVelocity;
        }

        //decelerating
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.f)
        {
            this->velocity.x = 0.f;
        }
    }
    else if (this->velocity.x < 0.f) // check for the negative x
    {
        //check for the maximum velocity
        if (this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }

        //decelerating
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.f)
        {
            this->velocity.x = 0.f;
        }
    }

    if (this->velocity.y > 0.f) // check for the positive y
    {
        //Check for the maximum velocity
        if (this->velocity.y > this->maxVelocity)
        {
            this->velocity.y = this->maxVelocity;
        }

        //decelerating
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.f)
        {
            this->velocity.y = 0.f;
        }
    }
    else if (this->velocity.y < 0.f) // check for the negative y
    {
        //check for the maximum velocity
        if (this->velocity.y < -this->maxVelocity)
        {
            this->velocity.y = -this->maxVelocity;
        }

        //decelerating
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.f)
        {
            this->velocity.y = 0.f;
        }
    }

    //Final Movement
    this->sprite.move(this->velocity * dt); //Move the sprite with velocity
}
