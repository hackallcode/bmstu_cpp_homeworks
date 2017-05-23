#include "AliveObject.h"
#include "GameScene.h"

aad::AliveObject::AliveObject()
    : parent_(nullptr)
    , health_(0.f)
    , maxHealth_(0.f)
    , armor_(0.f)
    , maxArmor_(0.f)
    , healthLabel_(nullptr)
    , armorLabel_(nullptr)
{}

aad::AliveObject::AliveObject(GameObject const* parent, float maxHealth, float maxArmor)
    : parent_(nullptr)
    , health_(0.f)
    , maxHealth_(maxHealth)
    , armor_(0.f)
    , maxArmor_(maxArmor)
    , healthLabel_(nullptr)
    , armorLabel_(nullptr)
{
    SetParent(parent);
    SetHealth(maxHealth_);
    SetArmor(0.f);
}

void aad::AliveObject::Damage(float power)
{
    if (power > GetArmor()) {
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

void aad::AliveObject::SetParent(GameObject const * parent)
{
    parent_ = parent;
    LabelsInit_();
}

void aad::AliveObject::SetHealth(float health)
{
    health_ = health;
    if (healthLabel_ != nullptr) {
        healthLabel_->setString(std::to_string(static_cast<int>(ceil(health_))));
    }
}

void aad::AliveObject::SetArmor(float armor)
{
    armor_ = armor;
    if (armorLabel_ != nullptr) {
        if (armor_ == 0) {
            armorLabel_->setString("");
        }
        else {
            armorLabel_->setString(std::to_string(static_cast<int>(ceil(armor_))));
        }
    }
}

aad::GameObject const * aad::AliveObject::GetParent()
{
    return parent_;
}

float aad::AliveObject::GetHealth() const
{
    return health_;
}

float aad::AliveObject::GetMaxHealth() const
{
    return maxHealth_;
}

float aad::AliveObject::GetArmor() const
{
    return armor_;
}

float aad::AliveObject::GetMaxArmor() const
{
    return maxArmor_;
}

cocos2d::CCLabelTTF* aad::AliveObject::GetHealthLabel() const
{
    return healthLabel_;
}

cocos2d::CCLabelTTF* aad::AliveObject::GetArmorLabel() const
{
    return armorLabel_;
}

void aad::AliveObject::LabelsInit_()
{
    if (parent_ != nullptr) {
        if (healthLabel_ == nullptr) {
            healthLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", HEALTH_FONT_SIZE, cocos2d::Size(parent_->GetW(), HEALTH_FONT_SIZE));
        }
        else {
            healthLabel_->setContentSize(cocos2d::Size(parent_->GetW(), HEALTH_FONT_SIZE));
        }
        if (armorLabel_ == nullptr) {
            armorLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", HEALTH_FONT_SIZE, cocos2d::Size(parent_->GetW(), HEALTH_FONT_SIZE));
        }
        else {
            armorLabel_->setContentSize(cocos2d::Size(parent_->GetW(), HEALTH_FONT_SIZE));
        }

        OnXUpdate_();
        OnYUpdate_();
        OnRightAlignmentUpdate_();
    }
}

void aad::AliveObject::OnXUpdate_()
{
    if (parent_ != nullptr) {
        if (healthLabel_ != nullptr) {
            healthLabel_->setPositionX(parent_->GetSprite()->getPositionX());
        }
        if (armorLabel_ != nullptr) {
            armorLabel_->setPositionX(parent_->GetSprite()->getPositionX());
        }
    }
}

void aad::AliveObject::OnYUpdate_()
{
    if (parent_ != nullptr) {
        if (healthLabel_ != nullptr) {
            healthLabel_->setPositionY(parent_->GetY() + parent_->GetH() + MARGIN_SIZE);
        }
        if (armorLabel_ != nullptr) {
            armorLabel_->setPositionY(parent_->GetY() + parent_->GetH() + 2 * MARGIN_SIZE + HEALTH_FONT_SIZE);
        }
    }
}

void aad::AliveObject::OnRightAlignmentUpdate_()
{
    if (parent_ != nullptr) {
        if (healthLabel_ != nullptr) {
            healthLabel_->setAnchorPoint(cocos2d::Vec2(parent_->IsRightAlignment() ? 1 : 0, 0));
        }
        if (armorLabel_ != nullptr) {
            armorLabel_->setAnchorPoint(cocos2d::Vec2(parent_->IsRightAlignment() ? 1 : 0, 0));
        }
    }
}
