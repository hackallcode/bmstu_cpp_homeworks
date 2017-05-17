#include "StrongCastleObject.h"
#include "GameScene.h"

aad::StrongCastleObject::StrongCastleObject()
    : CastleObject(1000, "castles/StrongCastle.png")
{}

size_t aad::StrongCastleObject::GetCost() const
{
    return GetClassCost();
}

size_t aad::StrongCastleObject::GetClassCost()
{
    return 500;
}
