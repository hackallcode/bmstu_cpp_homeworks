#ifndef __ALIVE_OBJECT_INCLUDED__
#define __ALIVE_OBJECT_INCLUDED__

#include "cocos2d.h"
#include <string>
#include "GameObject.h"

namespace aad {

    float const HEALTH_FONT_SIZE = 30.f;
    float const HEALTH_MARGIN = 20.f;
    size_t const MAX_ATTACK_COUNT = 20;

    class AliveObject abstract
    {
    public:
        AliveObject();
        AliveObject(GameObject& parent, float maxHealth, float maxArmor);

        virtual ~AliveObject() = default;

        bool Damage(float power);

        void SetParent(GameObject& parent);
        void SetHealth(float health);
        void SetArmor(float armor);
        void SetAttackCount(size_t count);

        float GetHealth() const;
        float GetMaxHealth() const;
        float GetArmor() const;
        float GetMaxArmor() const;
        size_t GetAttackCount() const;

    protected:
        void SetAlignment_(bool isRight);

    private:
        float health_;
        float maxHealth_;
        float armor_;
        float maxArmor_;
        cocos2d::CCLabelTTF* healthLabel_;
        cocos2d::CCLabelTTF* armorLabel_;
        size_t attackCount_;

        void LabelsInit_(GameObject& parent);
    };

}

#endif // __ALIVE_OBJECT_INCLUDED__