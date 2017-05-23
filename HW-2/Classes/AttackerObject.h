#ifndef __ATTACKER_OBJECT_INCLUDED__
#define __ATTACKER_OBJECT_INCLUDED__

#include <string>
#include "DynamicObject.h"
#include "AliveObject.h"

namespace aad {

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