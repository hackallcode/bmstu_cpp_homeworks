#ifndef __SIMPLE_CASTLE_OBJECT_INCLUDED__
#define __SIMPLE_CASTLE_OBJECT_INCLUDED__

#include "CastleObject.h"

namespace AttackAndDefend {

    class SimpleCastleObject
        : public CastleObject
    {
    public:
        SimpleCastleObject();

        virtual ~SimpleCastleObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __SIMPLE_CASTLE_OBJECT_INCLUDED__