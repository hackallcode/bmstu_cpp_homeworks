#include "CastleObject.h"
#include "GameScene.h"

aad::CastleObject::CastleObject()
    : StaticObject()
    , AliveObject()
{}

aad::CastleObject::CastleObject(float maxHealth, std::string const& fileName)
    : StaticObject(CASTLE_X_POSITION, CASTLE_Y_POSITION, fileName)
    , AliveObject(this, maxHealth, 2.f * maxHealth)
{}

size_t aad::CastleObject::GetCost() const
{
    return 0;
}

void aad::CastleObject::OnXUpdate_()
{
    StaticObject::OnXUpdate_();
    AliveObject::OnXUpdate_();
}

void aad::CastleObject::OnYUpdate_()
{
    StaticObject::OnYUpdate_();
    AliveObject::OnYUpdate_();
}

void aad::CastleObject::OnRightAlignmentUpdate_()
{
    StaticObject::OnRightAlignmentUpdate_();
    AliveObject::OnRightAlignmentUpdate_();
}