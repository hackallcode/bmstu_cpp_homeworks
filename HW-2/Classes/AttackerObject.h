#ifndef __ATTACKER_OBJECT_INCLUDED__
#define __ATTACKER_OBJECT_INCLUDED__

#include "DynamicObject.h"

namespace AttackAndDefend {

    class AttackerObject abstract
        : public DynamicObject
    {
    public:
        AttackerObject();
        AttackerObject(float speed, float maxHealth, float power, std::string const& fileName);

        virtual ~AttackerObject() = default;

        virtual void Update(Game* const scene) override;

        void Damage(float power);

        void SetHealth(float health);
        
        float GetHealth();
        float GetMaxHealth();
        float GetPower();
        cocos2d::CCLabelTTF * GetLabel();

    protected:
        float health_;
        float maxHealth_;
        float power_;
        cocos2d::CCLabelTTF * label_;

        virtual void onPositionUpdate_() override;

        void InitLabel_();
        void UpdateLabelPosition();        
    };

}

#endif // __ATTACKER_OBJECT_INCLUDED__