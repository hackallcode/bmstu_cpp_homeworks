#include "AttackerObject.h"
#include "GameScene.h"

aad::AttackerObject::AttackerObject()
    : DynamicObject()
    , AliveObject()
    , power_(0.f)
    , secondPower_(0.f)
    , level_(0)
    , cost_(0)
{}

aad::AttackerObject::AttackerObject(std::string const & fileName, float maxHealth, float power, float speed, size_t cost)
    : DynamicObject(ATTACKER_X_START, ATTACKER_Y_START, speed, 0.f, fileName)
    , AliveObject(*this, maxHealth, 0.f)
    , power_(power)
    , cost_(cost)
    , level_(0)
    , secondPower_(power)
{
}

aad::AttackerObject::AttackerObject(std::string const& fileName, float maxHealth, float power, float speed, size_t cost, int level, float secondPower)
    : DynamicObject(ATTACKER_X_START, ATTACKER_Y_START, speed, 0.f, fileName)
    , AliveObject(*this, maxHealth, 0.f)
    , power_(power)
    , cost_(cost)
    , level_(level)
    , secondPower_(secondPower)
{}

aad::AttackerObject::AttackerObject(AttackerType type)
    : AttackerObject(
          AttackerObject::GetClassFile(type)
        , AttackerObject::GetClassHealth_(type)
        , AttackerObject::GetClassPower_(type)
        , AttackerObject::GetClassSpeed_(type)
        , AttackerObject::GetClassCost(type)
        , AttackerObject::GetClassLevel_(type)
        , AttackerObject::GetClassSecondPower_(type)
    )
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

    SetAttackCount(0);
}

void aad::AttackerObject::Attack(Game* const scene)
{
    bool isAttackOther = false;
    for (std::shared_ptr<AttackerObject>& attacker : scene->getAttackers(!IsRightAlignment())) {
        float distance = scene->getContentSize().width - attacker->GetX() - attacker->GetW() - GetW() - GetX();
        if (distance <= ATTACKER_DISTANCE) {
            if (attacker->Damage(GetPower(attacker->GetLevel()) * scene->getMissedTime())) {
                isAttackOther = true;
                break;
            }
        }
    }

    if (!isAttackOther) {
        auto& castle = scene->getCastle(!IsRightAlignment());
        if (castle) {
            float distance = scene->getContentSize().width - castle->GetX() - castle->GetW() - GetW() - GetX();
            if (distance <= ATTACKER_DISTANCE) {
                castle->Damage(GetPower() * scene->getMissedTime());
            }
        }
    }
}

float aad::AttackerObject::GetPower() const
{
    return power_;
}

float aad::AttackerObject::GetPower(int level) const
{
    if (level == level_ + 2) {
        return secondPower_;
    }
    else {
        return power_;
    }
}

size_t aad::AttackerObject::GetCost() const
{
    return cost_;
}

int aad::AttackerObject::GetLevel() const
{
    return level_;
}

size_t aad::AttackerObject::GetClassCost(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_COST;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_COST;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_COST;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_COST;
    default:
        return ATTACKER_NO_0_COST;
    }
}

std::string aad::AttackerObject::GetClassFile(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_FILE;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_FILE;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_FILE;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_FILE;
    default:
        return ATTACKER_NO_0_FILE;
    }
}

void aad::AttackerObject::OnRightAlignmentUpdate_()
{
    DynamicObject::OnRightAlignmentUpdate_();
    AliveObject::SetAlignment_(IsRightAlignment());
}

float aad::AttackerObject::GetClassHealth_(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_HEALTH;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_HEALTH;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_HEALTH;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_HEALTH;
    default:
        return ATTACKER_NO_0_HEALTH;
    }
}

float aad::AttackerObject::GetClassPower_(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_POWER;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_POWER;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_POWER;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_POWER;
    default:
        return ATTACKER_NO_0_POWER;
    }
}

float aad::AttackerObject::GetClassSecondPower_(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_SECOND_POWER;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_SECOND_POWER;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_SECOND_POWER;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_SECOND_POWER;
    default:
        return ATTACKER_NO_0_SECOND_POWER;
    }
}

float aad::AttackerObject::GetClassSpeed_(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_SPEED;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_SPEED;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_SPEED;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_SPEED;
    default:
        return ATTACKER_NO_0_SPEED;
    }
}

int aad::AttackerObject::GetClassLevel_(AttackerType type)
{
    switch (type)
    {
    case aad::AttackerTypeNo1:
        return ATTACKER_NO_1_LEVEL;
    case aad::AttackerTypeNo2:
        return ATTACKER_NO_2_LEVEL;
    case aad::AttackerTypeNo3:
        return ATTACKER_NO_3_LEVEL;
    case aad::AttackerTypeNo4:
        return ATTACKER_NO_4_LEVEL;
    default:
        return ATTACKER_NO_0_LEVEL;
    }
}
