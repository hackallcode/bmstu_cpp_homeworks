#include "SimpleCastleObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

SimpleCastleObject::SimpleCastleObject()
    : CastleObject(300, "castles/SimpleCastle.png")
{}

size_t AttackAndDefend::SimpleCastleObject::GetCost() const
{
    return GetClassCost();
}

size_t AttackAndDefend::SimpleCastleObject::GetClassCost()
{
    return 50;
}
