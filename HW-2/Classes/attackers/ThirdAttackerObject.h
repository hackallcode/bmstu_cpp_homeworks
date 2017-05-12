#ifndef __THIRD_ATTACKER_OBJECT_INCLUDED__
#define __THIRD_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace AttackAndDefend {

    class ThirdAttackerObject
        : public AttackerObject
    {
    public:
        ThirdAttackerObject();

        virtual ~ThirdAttackerObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __THIRD_ATTACKER_OBJECT_INCLUDED__