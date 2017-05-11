#ifndef __SECOND_ATTACKER_OBJECT_INCLUDED__
#define __SECOND_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace AttackAndDefend {

    class SecondAttackerObject
        : public AttackerObject
    {
    public:
        SecondAttackerObject();

        virtual ~SecondAttackerObject() = default;
    };

}

#endif // __SECOND_ATTACKER_OBJECT_INCLUDED__