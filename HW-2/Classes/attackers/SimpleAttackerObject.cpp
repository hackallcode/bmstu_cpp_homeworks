#include "SimpleAttackerObject.h"
#include "GameScene.h"

aad::SimpleAttackerObject::SimpleAttackerObject()
    : AttackerObject(1.5, 10, 0.1, "attackers/SimpleAttacker.png")
{}

size_t aad::SimpleAttackerObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::SimpleAttackerObject::GetClassCost()
{
    return 10;
}
