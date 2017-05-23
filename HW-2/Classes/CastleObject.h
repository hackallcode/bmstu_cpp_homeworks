#ifndef __CASTLE_OBJECT_INCLUDED__
#define __CASTLE_OBJECT_INCLUDED__

#include <string>
#include "StaticObject.h"
#include "AliveObject.h"

namespace aad {

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