#ifndef __SECOND_ATTACKER_OBJECT_INCLUDED__
#define __SECOND_ATTACKER_OBJECT_INCLUDED__

#include "AttackerObject.h"

namespace aad {

    class SecondAttackerObject
        : public AttackerObject
    {
    public:
        SecondAttackerObject();

        virtual ~SecondAttackerObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __SECOND_ATTACKER_OBJECT_INCLUDED__