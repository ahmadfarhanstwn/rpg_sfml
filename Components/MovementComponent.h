#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states
{
    IDLE,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
private:
    sf::Sprite& sprite;
    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    /**Accessors**/
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;
    //checking status of players
    const bool getState(const short unsigned state) const;

    //Functions
    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);
};

#endif // MOVEMENTCOMPONENT_H
