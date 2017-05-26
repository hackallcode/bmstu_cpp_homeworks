#ifndef __CASTLE_NO_1_INCLUDED__
#define __CASTLE_NO_1_INCLUDED__

#include "CastleObject.h"

namespace aad {

    class CastleNo1
        : public CastleObject
    {
    public:
        CastleNo1();

        virtual ~CastleNo1() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __CASTLE_NO_1_INCLUDED__