#include "AttackerNo3.h"
#include "GameScene.h"

aad::AttackerNo3::AttackerNo3()
    : AttackerObject(ATTACKER_NO_3_HEALTH, ATTACKER_NO_3_POWER, ATTACKER_NO_3_SPEED, ATTACKER_NO_3_FILE)
{}

size_t aad::AttackerNo3::GetCost() const
{
    return GetClassCost();
}

size_t aad::AttackerNo3::GetClassCost()
{
    return ATTACKER_NO_3_COST;
}