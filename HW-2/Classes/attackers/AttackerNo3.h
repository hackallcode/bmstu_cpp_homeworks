#ifndef __ATTACKER_NO_3_INCLUDED__
#define __ATTACKER_NO_3_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class AttackerNo3
        : public AttackerObject
    {
    public:
        AttackerNo3();

        virtual ~AttackerNo3() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __ATTACKER_NO_3_INCLUDED__