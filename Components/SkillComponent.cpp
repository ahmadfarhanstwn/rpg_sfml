#include "SkillComponent.h"
#include "stdafx.h"

SkillComponent::SkillComponent()
{
    this->skills.push_back(SKILLS_LIST::HEALTH);
    this->skills.push_back(SKILLS_LIST::ACCURACY);
    this->skills.push_back(SKILLS_LIST::ATTACK);
    this->skills.push_back(SKILLS_LIST::ENDURANCE);
}

SkillComponent::~SkillComponent()
{
    //dtor
}

const int SkillComponent::getSkill(const int index) const
{
    if (index >= 0 && index < this->skills.size())
        return this->skills[index].getLevel();
    else
        throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST : " + index);
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
    if (skill >= 0 && skill < this->skills.size())
        return this->skills[skill].gainExp(exp);
    else
        throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST : " + skill);
}
