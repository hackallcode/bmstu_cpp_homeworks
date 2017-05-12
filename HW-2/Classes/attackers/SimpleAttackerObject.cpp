#include "SimpleAttackerObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

SimpleAttackerObject::SimpleAttackerObject()
    : AttackerObject(1.5, 10, 0.2, "attackers/SimpleAttacker.png")
{}

size_t AttackAndDefend::SimpleAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::SimpleAttackerObject::GetClassCost()
{
    return 10;
}
