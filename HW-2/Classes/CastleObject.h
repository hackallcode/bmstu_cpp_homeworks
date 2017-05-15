#ifndef __CASTLE_OBJECT_INCLUDED__
#define __CASTLE_OBJECT_INCLUDED__

#include "StaticObject.h"

namespace AttackAndDefend {

    class CastleObject abstract
        : public StaticObject
    {
    public:
        CastleObject();
        CastleObject(float maxHealth, std::string const& fileName);

        virtual ~CastleObject() = default;

        virtual void Update(Game* const scene) override;

        void Damage(float power);

        void SetHealth(float health);
        void SetArmor(float armor);

        float GetHealth() const;
        float GetMaxHealth() const;
        float GetArmor() const;
        float GetMaxArmor() const;
        cocos2d::CCLabelTTF * GetHealthLabel() const;
        cocos2d::CCLabelTTF * GetArmorLabel() const;

        virtual size_t GetCost() const;

    protected:
        float health_;
        float maxHealth_;
        float armor_;
        float maxArmor_;
        cocos2d::CCLabelTTF * healthLabel_;
        cocos2d::CCLabelTTF * armorLabel_;

        virtual void onPositionUpdate_() override;

        void InitLabels_();
        void UpdateLabelsPosition_();
    };

}

#endif // __CASTLE_OBJECT_INCLUDED__