#include "CastleObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

CastleObject::CastleObject()
    : StaticObject()
    , maxHealth_(0.f)
    , maxArmor_(0.f)
{
    InitLabels_();
    SetHealth(maxHealth_);
    SetArmor(0.f);
}

CastleObject::CastleObject(float maxHealth, std::string const& fileName)
    : StaticObject(MARGIN_SIZE, GROUND_HEIGHT, fileName)
    , maxHealth_(maxHealth)
    , maxArmor_(2.f * maxHealth)
{
    InitLabels_();
    SetHealth(maxHealth_);
    SetArmor(0.f);
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
    healthLabel_->setString(buf);
}

void CastleObject::SetArmor(float armor)
{
    armor_ = armor;
    char buf[10];
    _itoa_s(int(armor_), buf, 10);
    armorLabel_->setString(buf);
}

float CastleObject::GetHealth() const
{
    return health_;
}

float CastleObject::GetMaxHealth() const
{
    return maxHealth_;
}

float CastleObject::GetArmor() const
{
    return armor_;
}

float CastleObject::GetMaxArmor() const
{
    return maxArmor_;
}

cocos2d::CCLabelTTF * AttackAndDefend::CastleObject::GetHealthLabel() const
{
    return healthLabel_;
}

cocos2d::CCLabelTTF * AttackAndDefend::CastleObject::GetArmorLabel() const
{
    return armorLabel_;
}

size_t AttackAndDefend::CastleObject::GetCost() const
{
    return 0;
}

void AttackAndDefend::CastleObject::onPositionUpdate_()
{
    GameObject::onPositionUpdate_();
    UpdateLabelsPosition();
}

void AttackAndDefend::CastleObject::InitLabels_()
{
    healthLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    armorLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    UpdateLabelsPosition();
}

void AttackAndDefend::CastleObject::UpdateLabelsPosition()
{
    if (isRightAlignment_) {
        healthLabel_->setPosition(frameWidth_ - MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        healthLabel_->setAnchorPoint(cocos2d::Vec2(1, 0));
        armorLabel_->setPosition(frameWidth_ - MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE + 40);
        armorLabel_->setAnchorPoint(cocos2d::Vec2(1, 0));
    }
    else {
        healthLabel_->setPosition(MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        healthLabel_->setAnchorPoint(cocos2d::Vec2(0, 0));
        armorLabel_->setPosition(MARGIN_SIZE, GROUND_HEIGHT + GetH() + MARGIN_SIZE + 40);
        armorLabel_->setAnchorPoint(cocos2d::Vec2(0, 0));
    }
}
