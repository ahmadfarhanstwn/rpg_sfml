#include "AttributeComponent.h"
#include "stdafx.h"

AttributeComponent::AttributeComponent(int level)
{
    this->level = level;
    this->exp = 0;
    this->expNext = static_cast<int>((50/3) * (std::pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level+1) * 17) - 12));
    this->attributePoints = 2;

    this->vitality = 1;
    this->strength = 1;
    this->dexterity = 1;
    this->agility = 1;
    this->intelligence = 1;

    this->levelUp();
    this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
    //dtor
}

//Function
void AttributeComponent::gainExp(const int exp)
{
    this->exp += exp;

    this->levelUp();
}

void AttributeComponent::updateStats(const bool reset)
{
    this->hpMax = this->vitality * 9 + this->vitality + this->strength / 2 + this->intelligence / 5;
    this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
    this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
    this->accuracy = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
    this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
    this->luck = this->intelligence * 2 + this->intelligence / 5;

    if (reset)
    {
        this->hp = this->hpMax;
    }
}

void AttributeComponent::levelUp()
{
    while(this->exp >= this->expNext)
    {
        ++this->level;
        this->exp -= this->expNext;
        this->expNext = static_cast<int>((50/3) * (std::pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
        ++this->attributePoints;
    }
}

void AttributeComponent::update()
{
    this->levelUp();
}
