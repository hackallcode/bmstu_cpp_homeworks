#ifndef __SIMPLE_ATTACKER_OBJECT_INCLUDED__
#define __SIMPLE_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class SimpleAttackerObject
        : public AttackerObject
    {
    public:
        SimpleAttackerObject();

        virtual ~SimpleAttackerObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __SIMPLE_ATTACKER_OBJECT_INCLUDED__