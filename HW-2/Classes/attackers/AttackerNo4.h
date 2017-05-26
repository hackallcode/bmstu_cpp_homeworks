#ifndef __ATTACKER_NO_4_INCLUDED__
#define __ATTACKER_NO_4_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class AttackerNo4
        : public AttackerObject
    {
    public:
        AttackerNo4();

        virtual ~AttackerNo4() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __ATTACKER_NO_4_INCLUDED__