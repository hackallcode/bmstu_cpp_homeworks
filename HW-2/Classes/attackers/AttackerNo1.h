#ifndef __ATTACKER_NO_1_INCLUDED__
#define __ATTACKER_NO_1_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class AttackerNo1
        : public AttackerObject
    {
    public:
        AttackerNo1();

        virtual ~AttackerNo1() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __ATTACKER_NO_1_INCLUDED__