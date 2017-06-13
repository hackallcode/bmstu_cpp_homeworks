#include "AliveObject.h"
#include "GameScene.h"

aad::AliveObject::AliveObject()
    : health_(0.f)
    , maxHealth_(0.f)
    , armor_(0.f)
    , maxArmor_(0.f)
    , healthLabel_(nullptr)
    , armorLabel_(nullptr)
    , attackCount_(0)
{}

aad::AliveObject::AliveObject(GameObject& parent, float maxHealth, float maxArmor)
    : health_(0.f)
    , maxHealth_(maxHealth)
    , armor_(0.f)
    , maxArmor_(maxArmor)
    , healthLabel_(nullptr)
    , armorLabel_(nullptr)
    , attackCount_(0)
{
    SetParent(parent);
    SetHealth(maxHealth_);
    SetArmor(0.f);
}

bool aad::AliveObject::Damage(float power)
{
    if (attackCount_ >= MAX_ATTACK_COUNT) {
        return false;
    }

    ++attackCount_;
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
    return true;
}

void aad::AliveObject::SetParent(GameObject& parent)
{
    LabelsInit_(parent);
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

void aad::AliveObject::SetAttackCount(size_t count)
{
    attackCount_ = count;
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

size_t aad::AliveObject::GetAttackCount() const
{
    return attackCount_;
}

void aad::AliveObject::LabelsInit_(GameObject& parent)
{
    if (healthLabel_ != nullptr) {
        healthLabel_->release();
        healthLabel_ = nullptr;
    }
    if (armorLabel_ != nullptr) {
        armorLabel_->release();
        armorLabel_ = nullptr;
    }

    healthLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", HEALTH_FONT_SIZE, cocos2d::Size(parent.GetW(), HEALTH_FONT_SIZE));
    healthLabel_->setPosition(0, parent.GetH() + HEALTH_MARGIN);
    parent.GetSprite()->addChild(healthLabel_, 1);

    armorLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", HEALTH_FONT_SIZE, cocos2d::Size(parent.GetW(), HEALTH_FONT_SIZE));
    armorLabel_->setPosition(0, parent.GetH() + 2 * HEALTH_MARGIN + HEALTH_FONT_SIZE);
    parent.GetSprite()->addChild(armorLabel_, 1);

    SetAlignment_(parent.IsRightAlignment());
}

void aad::AliveObject::SetAlignment_(bool isRight)
{
    if (healthLabel_ != nullptr) {
        healthLabel_->setAnchorPoint(cocos2d::Vec2(isRight, 0));
        healthLabel_->setRotation3D(cocos2d::Vec3(0, (isRight ? 180 : 0), 0));
    }
    if (armorLabel_ != nullptr) {
        armorLabel_->setAnchorPoint(cocos2d::Vec2(isRight, 0));
        armorLabel_->setRotation3D(cocos2d::Vec3(0, (isRight ? 180 : 0), 0));
    }
}
