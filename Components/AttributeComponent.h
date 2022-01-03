#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
    //Levelling
    int level;
    int exp;
    int expNext;
    int attributePoints;

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
    AttributeComponent(int level);
    virtual ~AttributeComponent();

    //Functions
    void loseHp(const int hp);
    void gainHp(const int hp);
    void loseExp(const unsigned exp);
    void gainExp(const int exp);
    void updateStats(const bool reset);
    void levelUp();

    void update();
};

#endif // ATTRIBUTECOMPONENT_H
