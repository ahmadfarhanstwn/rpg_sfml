#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
    //Levelling
    unsigned level;
    unsigned exp;
    unsigned expNext;
    unsigned attributePoints;

    //Attributes
    int strength;
    int vitality;
    int dexterity;
    int agility;
    int intelligence;

    //Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int defence;
    int luck;

    //Const & Des
    AttributeComponent(unsigned level);
    virtual ~AttributeComponent();

    //Functions
    void gainExp(const unsigned exp);
    void updateStats(const bool reset);
    void levelUp();

    void update();
};

#endif // ATTRIBUTECOMPONENT_H
