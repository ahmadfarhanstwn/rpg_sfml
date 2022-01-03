#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include <Items.h>
class Items;

class MeleeWeapon : public Items
{
private:

protected:
    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;

    int damageMin;
    int damageMax;

public:
    MeleeWeapon();
    virtual ~MeleeWeapon();

    //Functions
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif // MELEEWEAPON_H
