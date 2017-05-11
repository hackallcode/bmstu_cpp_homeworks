#ifndef __SIMPLE_ATTACKER_OBJECT_INCLUDED__
#define __SIMPLE_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace AttackAndDefend {

    class SimpleAttackerObject
        : public AttackerObject
    {
    public:
        SimpleAttackerObject();

        virtual ~SimpleAttackerObject() = default;
    };

}

#endif // __SIMPLE_ATTACKER_OBJECT_INCLUDED__