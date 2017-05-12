#include "SecondAttackerObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

SecondAttackerObject::SecondAttackerObject()
    : AttackerObject(2.5, 20, 0.7, "attackers/SecondAttacker.png")
{}

size_t AttackAndDefend::SecondAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::SecondAttackerObject::GetClassCost()
{
    return 90;
}
