#ifndef __CASTLE_OBJECT_INCLUDED__
#define __CASTLE_OBJECT_INCLUDED__

#include <string>
#include "StaticObject.h"
#include "AliveObject.h"

namespace aad {

    const float CASTLE_X_POSITION = 20.f;
    const float CASTLE_Y_POSITION = 80.f;

    const float CASTLE_NO_1_COST = 50.f;
    const float CASTLE_NO_1_HEALTH = 300.f;
    const std::string CASTLE_NO_1_FILE = "castles/CastleNo1.png";

    const float CASTLE_NO_2_COST = 500.f;
    const float CASTLE_NO_2_HEALTH = 1000.f;
    const std::string CASTLE_NO_2_FILE = "castles/CastleNo2.png";

    class CastleObject abstract
        : public StaticObject, public AliveObject
    {
    public:
        CastleObject();
        CastleObject(float maxHealth, std::string const& fileName);

        virtual ~CastleObject() = default;

        virtual size_t GetCost() const;

    protected:
        virtual void OnXUpdate_() override;
        virtual void OnYUpdate_() override;
        virtual void OnRightAlignmentUpdate_() override;
    };

}

#endif // __CASTLE_OBJECT_INCLUDED__