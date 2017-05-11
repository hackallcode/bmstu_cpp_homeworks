#include "DynamicObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

DynamicObject::DynamicObject()
    : GameObject()
    , hSpeed_(0.f)
    , vSpeed_(0.f)
{}

DynamicObject::DynamicObject(float x, float y, float hSpeed, float vSpeed, cocos2d::Sprite* sprite)
    : GameObject(x, y, sprite)
    , hSpeed_(hSpeed)
    , vSpeed_(vSpeed)
{}

DynamicObject::DynamicObject(float x, float y, float hSpeed, float vSpeed, std::string const& fileName)
    : GameObject(x, y, fileName)
    , hSpeed_(hSpeed)
    , vSpeed_(vSpeed)
{}

void DynamicObject::Update(Game* const scene)
{
    SetY(GetY() + vSpeed_);
    SetX(GetX() + hSpeed_);
}

float DynamicObject::GetHSpeed()
{
    return hSpeed_;
}

float DynamicObject::GetVSpeed()
{
    return vSpeed_;
}

void DynamicObject::SetHSpeed(float speed)
{
    hSpeed_ = speed;
}

void DynamicObject::SetVSpeed(float speed)
{
    vSpeed_ = speed;
}