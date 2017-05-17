#include "ThirdAttackerObject.h"
#include "GameScene.h"

aad::ThirdAttackerObject::ThirdAttackerObject()
    : AttackerObject(1.5, 30, 1, "attackers/ThirdAttacker.png")
{}

size_t aad::ThirdAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::ThirdAttackerObject::GetClassCost()
{
    return 150;
}
