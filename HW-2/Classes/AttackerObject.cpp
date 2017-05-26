#include "AttackerObject.h"
#include "GameScene.h"

aad::AttackerObject::AttackerObject()
    : DynamicObject()
    , AliveObject()
    , power_(0.f)
{}

aad::AttackerObject::AttackerObject(float maxHealth, float power, float speed, std::string const& fileName)
    : DynamicObject(ATTACKER_X_START, ATTACKER_Y_START, speed, 0.f, fileName)
    , AliveObject(this, maxHealth, 0.f)
    , power_(power)
{}

void aad::AttackerObject::Update(Game* const scene)
{
    DynamicObject::Update(scene);

    for (std::shared_ptr<AttackerObject>& attacker : scene->getAttackers(!IsRightAlignment())) {
        float distance = scene->getContentSize().width - attacker->GetX() - attacker->GetW() - GetW() - GetX();
        if (distance < ATTACKER_DISTANCE) {
            SetX_(GetX() - (ATTACKER_DISTANCE - distance));
        }
    }

    auto& castle = scene->getCastle(!IsRightAlignment());
    if (castle) {
        float distance = scene->getContentSize().width - castle->GetX() - castle->GetW() - GetW() - GetX();
        if (distance < ATTACKER_DISTANCE) {
            SetX_(GetX() - (ATTACKER_DISTANCE - distance));
        }
    }
    OnPositionUpdate_();
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

float aad::AttackerObject::GetPower() const
{
    return power_;
}

size_t aad::AttackerObject::GetCost() const
{
    return 0;
}

void aad::AttackerObject::OnXUpdate_()
{
    DynamicObject::OnXUpdate_();
    AliveObject::OnXUpdate_();
}

void aad::AttackerObject::OnYUpdate_()
{
    DynamicObject::OnYUpdate_();
    AliveObject::OnYUpdate_();
}

void aad::AttackerObject::OnRightAlignmentUpdate_()
{
    DynamicObject::OnRightAlignmentUpdate_();
    AliveObject::OnRightAlignmentUpdate_();
}
