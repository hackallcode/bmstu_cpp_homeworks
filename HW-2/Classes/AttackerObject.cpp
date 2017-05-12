#include "AttackerObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

AttackerObject::AttackerObject()
    : DynamicObject()
    , maxHealth_(0.f)
    , power_(0.f)
{
    InitLabel_();
    SetHealth(maxHealth_);
}

AttackerObject::AttackerObject(float speed, float maxHealth, float power, std::string const& fileName)
    : DynamicObject(MARGIN_SIZE, GROUND_HEIGHT, speed, 0.f, fileName)
    , maxHealth_(maxHealth)
    , power_(power)
{
    InitLabel_();
    SetHealth(maxHealth_);
}

void AttackerObject::Update(Game* const scene)
{
    DynamicObject::Update(scene);

    std::vector<std::shared_ptr<AttackerObject>> attackers;
    if (IsRightAlignment()) {
        attackers = scene->leftAttackers_;
    }
    else {
        attackers = scene->rightAttackers_;
    }
    for (std::shared_ptr<AttackerObject>& attacker : attackers) {
        float attackerBorderX = scene->getContentSize().width - (attacker->GetX() + attacker->GetW()) - GetW();
        if (GetX() > attackerBorderX) {
            SetX(attackerBorderX);
        }
    }

    float maxDistance = 0;
    if (IsRightAlignment()) {
        maxDistance = scene->getContentSize().width - (scene->leftCastle_->GetW() + 2 * MARGIN_SIZE + GetW());
    }
    else {
        maxDistance = scene->getContentSize().width - (scene->rightCastle_->GetW() + 2 * MARGIN_SIZE + GetW());
    }
    if (GetX() > maxDistance) {
        SetX(maxDistance);
    }
}

void AttackAndDefend::AttackerObject::Attack(Game * const scene)
{
    bool isAttackOther = false;

    std::vector<std::shared_ptr<AttackerObject>> attackers;
    if (IsRightAlignment()) {
        attackers = scene->leftAttackers_;
    }
    else {
        attackers = scene->rightAttackers_;
    }
    for (std::shared_ptr<AttackerObject>& attacker : attackers) {
        float attackerBorderX = scene->getContentSize().width - (attacker->GetX() + attacker->GetW()) - GetW();
        if (GetX() == attackerBorderX) {
            attacker->Damage(GetPower());
            isAttackOther = true;
            break;
        }
    }

    if (!isAttackOther) {
        float maxDistance = 0;
        if (IsRightAlignment()) {
            maxDistance = scene->getContentSize().width - (scene->leftCastle_->GetW() + 2 * MARGIN_SIZE + GetW());
        }
        else {
            maxDistance = scene->getContentSize().width - (scene->rightCastle_->GetW() + 2 * MARGIN_SIZE + GetW());
        }
        if (GetX() == maxDistance) {
            if (IsRightAlignment()) {
                scene->leftCastle_->Damage(GetPower());
            }
            else {
                scene->rightCastle_->Damage(GetPower());
            }
        }
    }
}

void AttackAndDefend::AttackerObject::Damage(float power)
{
    SetHealth(GetHealth() - power);
    if (GetHealth() < 0) {
        SetHealth(0);
    }
}

void AttackerObject::SetHealth(float health)
{
    health_ = health;
    char buf[10];
    _itoa_s(ceil(health_), buf, 10);
    label_->setString(buf);
}

float AttackerObject::GetHealth() const
{
    return health_;
}

float AttackerObject::GetMaxHealth() const
{
    return maxHealth_;
}

float AttackerObject::GetPower() const
{
    return power_;
}

cocos2d::CCLabelTTF * AttackAndDefend::AttackerObject::GetLabel() const
{
    return label_;
}

size_t AttackAndDefend::AttackerObject::GetCost() const
{
    return 0;
}

void AttackAndDefend::AttackerObject::onPositionUpdate_()
{
    GameObject::onPositionUpdate_();
    UpdateLabelPosition();
}

void AttackAndDefend::AttackerObject::InitLabel_()
{
    label_ = cocos2d::CCLabelTTF::create("", "Helvetica", 30, cocos2d::Size(GetW(), 30));
    UpdateLabelPosition();
}

void AttackAndDefend::AttackerObject::UpdateLabelPosition()
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
