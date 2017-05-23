#ifndef __ALIVE_OBJECT_INCLUDED__
#define __ALIVE_OBJECT_INCLUDED__

#include "cocos2d.h"
#include <string>
#include "GameObject.h"

namespace aad {

    class AliveObject abstract
    {
    public:
        AliveObject();
        AliveObject(GameObject const* parent, float maxHealth, float maxArmor);

        virtual ~AliveObject() = default;

        virtual void Damage(float power);

        void SetParent(GameObject const* parent);
        void SetHealth(float health);
        void SetArmor(float armor);

        GameObject const* GetParent();
        float GetHealth() const;
        float GetMaxHealth() const;
        float GetArmor() const;
        float GetMaxArmor() const;
        cocos2d::CCLabelTTF * GetHealthLabel() const;
        cocos2d::CCLabelTTF * GetArmorLabel() const;

    protected:
        virtual void OnXUpdate_();
        virtual void OnYUpdate_();
        virtual void OnRightAlignmentUpdate_();

    private:
        GameObject const* parent_;
        float health_;
        float maxHealth_;
        float armor_;
        float maxArmor_;
        cocos2d::CCLabelTTF * healthLabel_;
        cocos2d::CCLabelTTF * armorLabel_;

        void LabelsInit_();
    };

}

#endif // __ALIVE_OBJECT_INCLUDED__