#include "AttackerNo4.h"
#include "GameScene.h"

aad::AttackerNo4::AttackerNo4()
    : AttackerObject(ATTACKER_NO_4_HEALTH, ATTACKER_NO_4_POWER, ATTACKER_NO_4_SPEED, ATTACKER_NO_4_FILE)
{}

size_t aad::AttackerNo4::GetCost() const
{
    return GetClassCost();
}

size_t aad::AttackerNo4::GetClassCost()
{
    return ATTACKER_NO_4_COST;
}