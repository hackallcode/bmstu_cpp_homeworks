#include "SecondAttackerObject.h"
#include "GameScene.h"

aad::SecondAttackerObject::SecondAttackerObject()
    : AttackerObject(SECOND_ATTACKER_HEALTH, SECOND_ATTACKER_POWER, SECOND_ATTACKER_SPEED, "attackers/SecondAttacker.png")
{}

size_t aad::SecondAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::SecondAttackerObject::GetClassCost()
{
    return SECOND_ATTACKER_COST;
}