#include "CastleObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

CastleObject::CastleObject()
    : StaticObject()
    , health_(0.f)
    , maxHealth_(0.f)
    , armor_(0.f)
    , maxArmor_(0.f)
{
    InitLabel_();
}

CastleObject::CastleObject(float maxHealth, std::string const& fileName)
    : StaticObject(MARGIN_SIZE, GROUND_HEIGHT, fileName)
    , health_(maxHealth)
    , maxHealth_(maxHealth)
    , armor_(0.f)
    , maxArmor_(2.f * maxHealth)
{
    InitLabel_();
    char buf[10];
    _itoa_s(int(health_), buf, 10);
    label_->setString(buf);
}

void CastleObject::Update(Game* const scene)
{
    StaticObject::Update(scene);
}

void AttackAndDefend::CastleObject::Damage(float power)
{
    if (GetArmor() - power < 0) {
        SetArmor(0);
        SetHealth(GetHealth() - (power - GetArmor()));
        if (GetHealth() < 0) {
            SetHealth(0);
        }
    }
    else {
        SetArmor(GetArmor() - power);
    }
}

void CastleObject::SetHealth(float health)
{
    health_ = health;
    char buf[10];
    _itoa_s(int(health_), buf, 10);
    label_->setString(buf);
}

void CastleObject::SetArmor(float armor)
{
    armor_ = armor;
}

float CastleObject::GetHealth()
{
    return health_;
}

float CastleObject::GetMaxHealth()
{
    return maxHealth_;
}

float CastleObject::GetArmor()
{
    return armor_;
}

float CastleObject::GetMaxArmor()
{
    return maxArmor_;
}

cocos2d::CCLabelTTF * AttackAndDefend::CastleObject::GetLabel()
{
    return label_;
}

void AttackAndDefend::CastleObject::onPositionUpdate_()
{
    GameObject::onPositionUpdate_();
    UpdateLabelPosition();
}

void AttackAndDefend::CastleObject::InitLabel_()
{
    label_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    UpdateLabelPosition();
}

void AttackAndDefend::CastleObject::UpdateLabelPosition()
{
    if (isRightAlignment_) {
        label_->setPosition(frameWidth_ - MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        label_->setAnchorPoint(cocos2d::Vec2(1, 0));
    }
    else {
        label_->setPosition(MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        label_->setAnchorPoint(cocos2d::Vec2(0, 0));
    }
}
