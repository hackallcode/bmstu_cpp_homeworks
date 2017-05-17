#include "SecondAttackerObject.h"
#include "GameScene.h"

aad::SecondAttackerObject::SecondAttackerObject()
    : AttackerObject(2.5, 20, 0.7, "attackers/SecondAttacker.png")
{}

size_t aad::SecondAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::SecondAttackerObject::GetClassCost()
{
    return 90;
}
