#include "SimpleAttackerObject.h"
#include "GameScene.h"

aad::SimpleAttackerObject::SimpleAttackerObject()
    : AttackerObject(SIMPLE_ATTACKER_HEALTH, SIMPLE_ATTACKER_POWER, SIMPLE_ATTACKER_SPEED, "attackers/SimpleAttacker.png")
{}

size_t aad::SimpleAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::SimpleAttackerObject::GetClassCost()
{
    return SIMPLE_ATTACKER_COST;
}