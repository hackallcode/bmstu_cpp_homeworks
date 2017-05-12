#include "StrongCastleObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

StrongCastleObject::StrongCastleObject()
    : CastleObject(1000, "castles/StrongCastle.png")
{}

size_t AttackAndDefend::StrongCastleObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::StrongCastleObject::GetClassCost()
{
    return 500;
}
