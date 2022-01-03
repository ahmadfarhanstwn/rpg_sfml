#include "stdafx.h"
#include "Player.h"

//init functions
void Player::initVariables()
{
    this->attacking = false;
}

void Player::initComponents()
{

}

void Player::initAnimations()
{
    this->animationComponent->addAnimation("IDLE",15.f,0,0,8,0,64,64);
    this->animationComponent->addAnimation("WALK_DOWN",11.f,0,1,3,1,64,64);
    this->animationComponent->addAnimation("WALK_LEFT",11.f,4,1,7,1,64,64);
    this->animationComponent->addAnimation("WALK_RIGHT",11.f,8,1,11,1,64,64);
    this->animationComponent->addAnimation("WALK_UP",11.f,12,1,15,1,64,64);
    this->animationComponent->addAnimation("ATTACK",2.f,0,2,13,2,64,64);
}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariables();

    this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 44.f);
    this->createMovementComponent(200.f, 1600.f, 1000.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);

    this->setPosition(x,y);
    this->initAnimations();
}

Player::~Player()
{
    //dtor
}

void Player::updateAttack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
//        this->attacking = true;
    }
}

//Accessors
AttributeComponent* Player::getAttributeComponent()
{
    return this->attributeComponent;
}

//Functions
void Player::loseHp(const int hp)
{
    this->attributeComponent->loseHp(hp);
}

void Player::gainHp(const int hp)
{
    this->attributeComponent->gainHp(hp);
}

void Player::loseExp(const unsigned exp)
{
    this->attributeComponent->loseExp(exp);
}

void Player::gainExp(const unsigned exp)
{
    this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float& dt)
{
    if (this->attacking)
    {

    }
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt);
    }
    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, -this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, -this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
//    this->attributeComponent->update();

    this->movementComponent->update(dt);

    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();

    this->sword.update(mouse_pos_view, this->getCenter());
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool showHitbox)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);
        target.draw(this->sprite, shader);

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);
        this->sword.render(target, shader);
    }
    else
    {
        target.draw(this->sprite);
        this->sword.render(target);
    }
    if(showHitbox) this->hitboxComponent->render(target);
}
