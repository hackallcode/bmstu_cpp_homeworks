#ifndef __FIRST_ATTACKER_OBJECT_INCLUDED__
#define __FIRST_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace AttackAndDefend {

    class FirstAttackerObject
        : public AttackerObject
    {
    public:
        FirstAttackerObject();

        virtual ~FirstAttackerObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __FIRST_ATTACKER_OBJECT_INCLUDED__