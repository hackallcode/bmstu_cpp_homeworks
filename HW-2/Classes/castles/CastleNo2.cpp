#include "CastleNo2.h"
#include "GameScene.h"

aad::CastleNo2::CastleNo2()
    : CastleObject(CASTLE_NO_2_HEALTH, CASTLE_NO_2_FILE)
{}

size_t aad::CastleNo2::GetCost() const
{
    return GetClassCost();
}

size_t aad::CastleNo2::GetClassCost()
{
    return CASTLE_NO_2_COST;
}
