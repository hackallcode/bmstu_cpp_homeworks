#include "ThirdAttackerObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

ThirdAttackerObject::ThirdAttackerObject()
    : AttackerObject(1.5, 30, 1, "attackers/ThirdAttacker.png")
{}

size_t AttackAndDefend::ThirdAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::ThirdAttackerObject::GetClassCost()
{
    return 150;
}
