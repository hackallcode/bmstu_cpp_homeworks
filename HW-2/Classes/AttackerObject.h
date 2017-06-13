#ifndef __ATTACKER_OBJECT_INCLUDED__
#define __ATTACKER_OBJECT_INCLUDED__

#include <string>
#include "DynamicObject.h"
#include "AliveObject.h"

namespace aad {

    float const ATTACKER_DISTANCE = 1.f;
    float const ATTACKER_X_START = 20.f;
    float const ATTACKER_Y_START = 80.f;

    std::string const ATTACKER_NO_0_FILE = "res/attackers/AttackerNo0.png";
    float const ATTACKER_NO_0_HEALTH = 0.f;
    float const ATTACKER_NO_0_POWER = 0.f;
    float const ATTACKER_NO_0_SPEED = 0.f;
    size_t const ATTACKER_NO_0_COST = 0.f;
    int const ATTACKER_NO_0_LEVEL = 0;
    float const ATTACKER_NO_0_SECOND_POWER = 0.f;

    std::string const ATTACKER_NO_1_FILE = "res/attackers/AttackerNo1.png";
    float const ATTACKER_NO_1_HEALTH = 10.f;
    float const ATTACKER_NO_1_POWER = 2.f;
    float const ATTACKER_NO_1_SPEED = 90.f;
    size_t const ATTACKER_NO_1_COST = 10.f;
    int const ATTACKER_NO_1_LEVEL = 1;
    float const ATTACKER_NO_1_SECOND_POWER = 7.27f;

    std::string const ATTACKER_NO_2_FILE = "res/attackers/AttackerNo2.png";
    float const ATTACKER_NO_2_HEALTH = 50.f;
    float const ATTACKER_NO_2_POWER = 7.2f;
    float const ATTACKER_NO_2_SPEED = 180.f;
    size_t const ATTACKER_NO_2_COST = 50.f;
    int const ATTACKER_NO_2_LEVEL = 2;
    float const ATTACKER_NO_2_SECOND_POWER = 26.18f;

    std::string const ATTACKER_NO_3_FILE = "res/attackers/AttackerNo3.png";
    float const ATTACKER_NO_3_HEALTH = 250.f;
    float const ATTACKER_NO_3_POWER = 25.92f;
    float const ATTACKER_NO_3_SPEED = 150.f;
    size_t const ATTACKER_NO_3_COST = 250.f;
    int const ATTACKER_NO_3_LEVEL = 3;
    float const ATTACKER_NO_3_SECOND_POWER = 94.24f;

    std::string const ATTACKER_NO_4_FILE = "res/attackers/AttackerNo4.png";
    float const ATTACKER_NO_4_HEALTH = 1250.f;
    float const ATTACKER_NO_4_POWER = 93.31f;
    float const ATTACKER_NO_4_SPEED = 90.f;
    size_t const ATTACKER_NO_4_COST = 1250.f;
    int const ATTACKER_NO_4_LEVEL = 4;
    float const ATTACKER_NO_4_SECOND_POWER = 339.27f;

    enum AttackerType {
        AttackerTypeNo1 = 1
        , AttackerTypeNo2
        , AttackerTypeNo3
        , AttackerTypeNo4
    };

    class AttackerObject
        : public DynamicObject, public AliveObject
    {
    public:
        AttackerObject();
        AttackerObject(std::string const& fileName, float maxHealth, float power, float speed, size_t cost);
        AttackerObject(std::string const& fileName, float maxHealth, float power, float speed, size_t cost, int level, float secondPower);
        AttackerObject(AttackerType type);

        virtual ~AttackerObject() = default;

        virtual void Update(Game* const scene) override;
        void Attack(Game* const scene);

        float GetPower() const;
        float GetPower(int level) const;
        size_t GetCost() const;
        int GetLevel() const;

        static std::string GetClassFile(AttackerType type);
        static size_t GetClassCost(AttackerType type);

    protected:
        virtual void OnRightAlignmentUpdate_() override;

    private:
        float power_;
        float secondPower_;
        size_t cost_;
        int level_;

        static float GetClassHealth_(AttackerType type);
        static float GetClassPower_(AttackerType type);
        static float GetClassSpeed_(AttackerType type);
        static int GetClassLevel_(AttackerType type);
        static float GetClassSecondPower_(AttackerType type);
    };

}

#endif // __ATTACKER_OBJECT_INCLUDED__