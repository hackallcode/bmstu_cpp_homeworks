#include "FirstAttackerObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

FirstAttackerObject::FirstAttackerObject()
    : AttackerObject(3.5, 15, 0.4, "attackers/FirstAttacker.png")
{}

size_t AttackAndDefend::FirstAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::FirstAttackerObject::GetClassCost()
{
    return 40;
}
