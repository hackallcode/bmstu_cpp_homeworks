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
    };

}

#endif // __THIRD_ATTACKER_OBJECT_INCLUDED__