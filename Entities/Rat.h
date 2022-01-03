#ifndef RAT_H
#define RAT_H

#include <Enemy.h>


class Rat : public Enemy
{
private:
    void initVariables();
    void initAnimations();

public:
    Rat(float x, float y, sf::Texture& texture_sheet);
    virtual ~Rat();

    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool showHitbox = false);
};

#endif // RAT_H
