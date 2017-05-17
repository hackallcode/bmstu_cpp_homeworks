#include "AttackerObject.h"
#include "GameScene.h"

aad::AttackerObject::AttackerObject()
    : DynamicObject()
    , maxHealth_(0.f)
    , power_(0.f)
{
    InitLabel_();
    SetHealth(maxHealth_);
}

aad::AttackerObject::AttackerObject(float speed, float maxHealth, float power, std::string const& fileName)
    : DynamicObject(MARGIN_SIZE, GROUND_HEIGHT, speed, 0.f, fileName)
    , maxHealth_(maxHealth)
    , power_(power)
{
    InitLabel_();
    SetHealth(maxHealth_);
}

void aad::AttackerObject::Update(Game* const scene)
{
    DynamicObject::Update(scene);

    for (std::shared_ptr<AttackerObject>& attacker : scene->getAttackers(!IsRightAlignment())) {
        float distance = scene->getContentSize().width - attacker->GetX() - attacker->GetW() - GetW() - GetX();
        if (distance < ATTACKER_DISTANCE) {
            SetX(GetX() - (ATTACKER_DISTANCE - distance));
        }
    }

    auto& castle = scene->getCastle(!IsRightAlignment());
    if (castle) {
        float distance = scene->getContentSize().width - castle->GetX() - castle->GetW() - GetW() - GetX();
        if (distance < ATTACKER_DISTANCE) {
            SetX(GetX() - (ATTACKER_DISTANCE - distance));
        }
    }
}

void aad::AttackerObject::Attack(Game* const scene)
{
    bool isAttackOther = false;
    for (std::shared_ptr<AttackerObject>& attacker : scene->getAttackers(!IsRightAlignment())) {
        float distance = scene->getContentSize().width - attacker->GetX() - attacker->GetW() - GetW() - GetX();
        if (distance <= ATTACKER_DISTANCE) {
            attacker->Damage(GetPower());
            isAttackOther = true;
            break;
        }
    }

    if (!isAttackOther) {
        auto& castle = scene->getCastle(!IsRightAlignment());
        if (castle) {
            float distance = scene->getContentSize().width - castle->GetX() - castle->GetW() - GetW() - GetX();
            if (distance <= ATTACKER_DISTANCE) {
                castle->Damage(GetPower());
            }
        }
    }
}

void aad::AttackerObject::Damage(float power)
{
    SetHealth(GetHealth() - power);
    if (GetHealth() < 0) {
        SetHealth(0);
    }
}

void aad::AttackerObject::SetHealth(float health)
{
    health_ = health;
    char buf[10];
    _itoa_s(ceil(health_), buf, 10);
    label_->setString(buf);
}

float aad::AttackerObject::GetHealth() const
{
    return health_;
}

float aad::AttackerObject::GetMaxHealth() const
{
    return maxHealth_;
}

float aad::AttackerObject::GetPower() const
{
    return power_;
}

cocos2d::CCLabelTTF * aad::AttackerObject::GetLabel() const
{
    return label_;
}

size_t aad::AttackerObject::GetCost() const
{
    return 0;
}

void aad::AttackerObject::onPositionUpdate_()
{
    GameObject::onPositionUpdate_();
    UpdateLabelPosition();
}

void aad::AttackerObject::InitLabel_()
{
    label_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    UpdateLabelPosition();
}

void aad::AttackerObject::UpdateLabelPosition()
{
    if (isRightAlignment_) {
        label_->setPosition(frameWidth_ - GetX(), GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        label_->setAnchorPoint(cocos2d::Vec2(1, 0));
    }
    else {
        label_->setPosition(GetX(), GROUND_HEIGHT + GetH() + MARGIN_SIZE);
        label_->setAnchorPoint(cocos2d::Vec2(0, 0));
    }
}
