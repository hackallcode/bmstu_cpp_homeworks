#include "CastleObject.h"
#include "GameScene.h"

aad::CastleObject::CastleObject()
    : StaticObject()
    , AliveObject()
    , cost_(0)
{}

aad::CastleObject::CastleObject(float maxHealth, std::string const& fileName, size_t cost)
    : StaticObject(CASTLE_X_POSITION, CASTLE_Y_POSITION, fileName)
    , AliveObject(*this, maxHealth, 2.f * maxHealth)
    , cost_(cost)
{}

aad::CastleObject::CastleObject(CastleType type)
    : CastleObject(
          CastleObject::GetClassHealth_(type)
        , CastleObject::GetClassFile(type)
        , CastleObject::GetClassCost(type)
    )
{}

void aad::CastleObject::Update(Game * const scene)
{
    SetAttackCount(0);
}

size_t aad::CastleObject::GetCost() const
{
    return cost_;
}

size_t aad::CastleObject::GetClassCost(CastleType type)
{
    switch (type)
    {
    case aad::CastleTypeNo1:
        return CASTLE_NO_1_COST;
    case aad::CastleTypeNo2:
        return CASTLE_NO_2_COST;
    default:
        return CASTLE_NO_0_COST;
    }
}

std::string aad::CastleObject::GetClassFile(CastleType type)
{
    switch (type)
    {
    case aad::CastleTypeNo1:
        return CASTLE_NO_1_FILE;
    case aad::CastleTypeNo2:
        return CASTLE_NO_2_FILE;
    default:
        return CASTLE_NO_0_FILE;
    }
}

void aad::CastleObject::OnRightAlignmentUpdate_()
{
    StaticObject::OnRightAlignmentUpdate_();
    AliveObject::SetAlignment_(IsRightAlignment());
}

float aad::CastleObject::GetClassHealth_(CastleType type)
{
    switch (type)
    {
    case aad::CastleTypeNo1:
        return CASTLE_NO_1_HEALTH;
    case aad::CastleTypeNo2:
        return CASTLE_NO_2_HEALTH;
    default:
        return CASTLE_NO_0_HEALTH;
    }
}