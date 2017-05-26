#ifndef __CASTLE_NO_2_INCLUDED__
#define __CASTLE_NO_2_INCLUDED__

#include "CastleObject.h"

namespace aad {

    class CastleNo2
        : public CastleObject
    {
    public:
        CastleNo2();

        virtual ~CastleNo2() = default;

        virtual size_t GetCost() const override;
        static size_t GetClassCost();
    };

}

#endif // __CASTLE_NO_2_INCLUDED__