#ifndef __STRONG_CASTLE_OBJECT_INCLUDED__
#define __STRONG_CASTLE_OBJECT_INCLUDED__

#include "CastleObject.h"

namespace AttackAndDefend {

    class StrongCastleObject
        : public CastleObject
    {
    public:
        StrongCastleObject();

        virtual ~StrongCastleObject() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __STRONG_CASTLE_OBJECT_INCLUDED__