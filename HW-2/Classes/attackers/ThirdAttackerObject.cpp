#include "ThirdAttackerObject.h"
#include "GameScene.h"

aad::ThirdAttackerObject::ThirdAttackerObject()
    : AttackerObject(THIRD_ATTACKER_HEALTH, THIRD_ATTACKER_POWER, THIRD_ATTACKER_SPEED, "attackers/ThirdAttacker.png")
{}

size_t aad::ThirdAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::ThirdAttackerObject::GetClassCost()
{
    return THIRD_ATTACKER_COST;
}