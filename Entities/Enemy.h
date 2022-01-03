#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy : public Entity
{
private:
//    EnemySpawner& enemySpawner;

    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    Enemy();
    virtual ~Enemy();

    virtual void updateAnimation(const float& dt) = 0;
    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool showHitbox = false) = 0;
};

#endif // ENEMY_H
