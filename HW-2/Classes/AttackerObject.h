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
        void Attack(Game* const scene);

        void Damage(float power);

        void SetHealth(float health);
        
        float GetHealth() const;
        float GetMaxHealth() const;
        float GetPower() const;
        cocos2d::CCLabelTTF * GetLabel() const;

        virtual size_t GetCost() const;

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