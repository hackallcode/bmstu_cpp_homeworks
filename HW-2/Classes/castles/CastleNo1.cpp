#include "CastleNo1.h"
#include "GameScene.h"

aad::CastleNo1::CastleNo1()
    : CastleObject(CASTLE_NO_1_HEALTH, CASTLE_NO_1_FILE)
{}

size_t aad::CastleNo1::GetCost() const
{
    return GetClassCost();
}

size_t aad::CastleNo1::GetClassCost()
{
    return CASTLE_NO_1_COST;
}
