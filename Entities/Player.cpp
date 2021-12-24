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

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariables();
    this->setPosition(x,y);

    this->createHitboxComponent(this->sprite, 10.f, 5.f, 44.f, 44.f);
    this->createMovementComponent(200.f, 1500.f, 900.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);

    this->animationComponent->addAnimation("IDLE",15.f,0,0,8,0,64,64);
    this->animationComponent->addAnimation("WALK_DOWN",12.f,0,1,3,1,64,64);
    this->animationComponent->addAnimation("WALK_LEFT",12.f,4,1,7,1,64,64);
    this->animationComponent->addAnimation("WALK_RIGHT",12.f,8,1,11,1,64,64);
    this->animationComponent->addAnimation("WALK_UP",12.f,12,1,15,1,64,64);
    this->animationComponent->addAnimation("ATTACK",2.f,0,2,13,2,64,64);
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
    this->attributeComponent->hp -= hp;

    if (this->attributeComponent->hp < 0)
        this->attributeComponent->hp = 0;
}

void Player::gainHp(const int hp)
{
    this->attributeComponent->hp += hp;

    if (this->attributeComponent->hp > this->attributeComponent->hpMax)
        this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseExp(const unsigned exp)
{
    this->attributeComponent->exp -= exp;

    if (this->attributeComponent->exp < 0)
        this->attributeComponent->exp = 0;
}

void Player::gainExp(const unsigned exp)
{
    this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float& dt)
{
    if (this->attacking)
    {
        //if this is attacking, change the origin
        if(this->sprite.getScale().x > 0.f)
        {
            this->sprite.setOrigin(96.f, 0.f);
        }
        else
        {
            this->sprite.setOrigin(258.f + 96.f, 0.f);
        }

        if(this->animationComponent->play("ATTACK", dt, true))
        {
            this->attacking = false;
            //return to to normal
            if(this->sprite.getScale().x > 0.f)
            {
                this->sprite.setOrigin(0.f, 0.f);
            }
            else
            {
                this->sprite.setOrigin(258.f, 0.f);
            }
        }
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

void Player::update(const float& dt)
{
//    this->attributeComponent->update();

    this->movementComponent->update(dt);

    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool showHitbox)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", this->getCenter());
        target.draw(this->sprite, shader);
    }
    else
    {
        target.draw(this->sprite);
    }
    if(showHitbox) this->hitboxComponent->render(target);
}
