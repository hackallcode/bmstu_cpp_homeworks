#ifndef __ATTACKER_OBJECT_INCLUDED__
#define __ATTACKER_OBJECT_INCLUDED__

#include <string>
#include "DynamicObject.h"
#include "AliveObject.h"

namespace aad {

    const float ATTACKER_DISTANCE = 1.f;
    const float ATTACKER_X_START = 20.f;
    const float ATTACKER_Y_START = 80.f;

    const float ATTACKER_NO_1_COST = 10.f;
    const float ATTACKER_NO_1_HEALTH = 10.f;
    const float ATTACKER_NO_1_POWER = 0.2f;
    const float ATTACKER_NO_1_SPEED = 1.5f;
    const std::string ATTACKER_NO_1_FILE = "attackers/AttackerNo1.png";

    const float ATTACKER_NO_2_COST = 40.f;
    const float ATTACKER_NO_2_HEALTH = 70.f;
    const float ATTACKER_NO_2_POWER = 0.3f;
    const float ATTACKER_NO_2_SPEED = 3.f;
    const std::string ATTACKER_NO_2_FILE = "attackers/AttackerNo2.png";

    const float ATTACKER_NO_3_COST = 90.f;
    const float ATTACKER_NO_3_HEALTH = 145.f;
    const float ATTACKER_NO_3_POWER = 0.45f;
    const float ATTACKER_NO_3_SPEED = 2.5f;
    const std::string ATTACKER_NO_3_FILE = "attackers/AttackerNo3.png";

    const float ATTACKER_NO_4_COST = 150.f;
    const float ATTACKER_NO_4_HEALTH = 175.f;
    const float ATTACKER_NO_4_POWER = 0.68f;
    const float ATTACKER_NO_4_SPEED = 1.5f;
    const std::string ATTACKER_NO_4_FILE = "attackers/AttackerNo4.png";

    class AttackerObject abstract
        : public DynamicObject, public AliveObject
    {
    public:
        AttackerObject();
        AttackerObject(float maxHealth, float power, float speed, std::string const& fileName);

        virtual ~AttackerObject() = default;

        virtual void Update(Game* const scene) override;
        void Attack(Game* const scene);

        float GetPower() const;

        virtual size_t GetCost() const;

    protected:        
        virtual void OnXUpdate_() override;
        virtual void OnYUpdate_() override;
        virtual void OnRightAlignmentUpdate_() override;

    private:
        float power_;
    };

}

#endif // __ATTACKER_OBJECT_INCLUDED__