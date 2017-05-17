#include "FirstAttackerObject.h"
#include "GameScene.h"

aad::FirstAttackerObject::FirstAttackerObject()
    : AttackerObject(3, 15, 0.3, "attackers/FirstAttacker.png")
{}

size_t aad::FirstAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::FirstAttackerObject::GetClassCost()
{
    return 40;
}
