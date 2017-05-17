#include "SimpleCastleObject.h"
#include "GameScene.h"

aad::SimpleCastleObject::SimpleCastleObject()
    : CastleObject(300, "castles/SimpleCastle.png")
{}

size_t aad::SimpleCastleObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::SimpleCastleObject::GetClassCost()
{
    return 50;
}
