#include "AttackerNo1.h"
#include "GameScene.h"

aad::AttackerNo1::AttackerNo1()
    : AttackerObject(ATTACKER_NO_1_HEALTH, ATTACKER_NO_1_POWER, ATTACKER_NO_1_SPEED, ATTACKER_NO_1_FILE)
{}

size_t aad::AttackerNo1::GetCost() const
{
    return GetClassCost();
}

size_t aad::AttackerNo1::GetClassCost()
{
    return ATTACKER_NO_1_COST;
}