#include "CastleObject.h"
#include "GameScene.h"

aad::CastleObject::CastleObject()
    : StaticObject()
    , maxHealth_(0.f)
    , maxArmor_(0.f)
{
    InitLabels_();
    SetHealth(maxHealth_);
    SetArmor(0.f);
}

aad::CastleObject::CastleObject(float maxHealth, std::string const& fileName)
    : StaticObject(MARGIN_SIZE, GROUND_HEIGHT, fileName)
    , maxHealth_(maxHealth)
    , maxArmor_(2.f * maxHealth)
{
    InitLabels_();
    SetHealth(maxHealth_);
    SetArmor(0.f);
}

void aad::CastleObject::Damage(float power)
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

void aad::CastleObject::SetHealth(float health)
{
    health_ = health;
    char buf[10];
    _itoa_s(int(health_), buf, 10);
    healthLabel_->setString(buf);
}

void aad::CastleObject::SetArmor(float armor)
{
    armor_ = armor;
    char buf[10];
    _itoa_s(int(armor_), buf, 10);
    armorLabel_->setString(buf);
}

float aad::CastleObject::GetHealth() const
{
    return health_;
}

float aad::CastleObject::GetMaxHealth() const
{
    return maxHealth_;
}

float aad::CastleObject::GetArmor() const
{
    return armor_;
}

float aad::CastleObject::GetMaxArmor() const
{
    return maxArmor_;
}

cocos2d::CCLabelTTF * aad::CastleObject::GetHealthLabel() const
{
    return healthLabel_;
}

cocos2d::CCLabelTTF * aad::CastleObject::GetArmorLabel() const
{
    return armorLabel_;
}

size_t aad::CastleObject::GetCost() const
{
    return 0;
}

void aad::CastleObject::onPositionUpdate_()
{
    GameObject::onPositionUpdate_();
    UpdateLabelsPosition_();
}

void aad::CastleObject::InitLabels_()
{
    healthLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    armorLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    UpdateLabelsPosition_();
}

void aad::CastleObject::UpdateLabelsPosition_()
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
