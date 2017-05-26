#ifndef __ATTACKER_NO_2_OBJECT_INCLUDED__
#define __ATTACKER_NO_2_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class AttackerNo2
        : public AttackerObject
    {
    public:
        AttackerNo2();

        virtual ~AttackerNo2() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __ATTACKER_NO_2_OBJECT_INCLUDED__