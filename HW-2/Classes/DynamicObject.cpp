#include "DynamicObject.h"
#include "GameScene.h"

aad::DynamicObject::DynamicObject()
    : GameObject()
    , hSpeed_(0.f)
    , vSpeed_(0.f)
{}

aad::DynamicObject::DynamicObject(float x, float y, float hSpeed, float vSpeed, cocos2d::Sprite* sprite)
    : GameObject(x, y, sprite)
    , hSpeed_(hSpeed)
    , vSpeed_(vSpeed)
{}

aad::DynamicObject::DynamicObject(float x, float y, float hSpeed, float vSpeed, std::string const& fileName)
    : GameObject(x, y, fileName)
    , hSpeed_(hSpeed)
    , vSpeed_(vSpeed)
{}

void aad::DynamicObject::Update(Game* const scene)
{
    SetY(GetY() + vSpeed_);
    SetX(GetX() + hSpeed_);
}

float aad::DynamicObject::GetHSpeed() const
{
    return hSpeed_;
}

float aad::DynamicObject::GetVSpeed() const
{
    return vSpeed_;
}

void aad::DynamicObject::SetHSpeed(float speed)
{
    hSpeed_ = speed;
}

void aad::DynamicObject::SetVSpeed(float speed)
{
    vSpeed_ = speed;
}