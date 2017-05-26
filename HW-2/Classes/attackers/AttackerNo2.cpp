#include "AttackerNo2.h"
#include "GameScene.h"

aad::AttackerNo2::AttackerNo2()
    : AttackerObject(ATTACKER_NO_2_HEALTH, ATTACKER_NO_2_POWER, ATTACKER_NO_2_SPEED, ATTACKER_NO_2_FILE)
{}

size_t aad::AttackerNo2::GetCost() const
{
    return GetClassCost();
}

size_t aad::AttackerNo2::GetClassCost()
{
    return ATTACKER_NO_2_COST;
}