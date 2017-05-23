#include "FirstAttackerObject.h"
#include "GameScene.h"

aad::FirstAttackerObject::FirstAttackerObject()
    : AttackerObject(FIRST_ATTACKER_HEALTH, FIRST_ATTACKER_POWER, FIRST_ATTACKER_SPEED, "attackers/FirstAttacker.png")
{}

size_t aad::FirstAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::FirstAttackerObject::GetClassCost()
{
    return FIRST_ATTACKER_COST;
}