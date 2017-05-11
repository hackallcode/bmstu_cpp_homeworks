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

        float GetHealth();
        float GetMaxHealth();
        float GetArmor();
        float GetMaxArmor();
        cocos2d::CCLabelTTF * GetLabel();

    protected:
        float health_;
        float maxHealth_;
        float armor_;
        float maxArmor_;
        cocos2d::CCLabelTTF * label_;

        virtual void onPositionUpdate_() override;

        void InitLabel_();
        void UpdateLabelPosition();
    };

}

#endif // __CASTLE_OBJECT_INCLUDED__