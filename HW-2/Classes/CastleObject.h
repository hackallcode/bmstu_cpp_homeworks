#ifndef __CASTLE_OBJECT_INCLUDED__
#define __CASTLE_OBJECT_INCLUDED__

#include <string>
#include "StaticObject.h"
#include "AliveObject.h"

namespace aad {

    float const CASTLE_X_POSITION = 20.f;
    float const CASTLE_Y_POSITION = 80.f;

    float const CASTLE_NO_0_HEALTH = 0.f;
    std::string const CASTLE_NO_0_FILE = "res/castles/CastleNo0.png";
    size_t const CASTLE_NO_0_COST = 0.f;

    float const CASTLE_NO_1_HEALTH = 300.f;
    std::string const CASTLE_NO_1_FILE = "res/castles/CastleNo1.png";
    size_t const CASTLE_NO_1_COST = 50.f;

    float const CASTLE_NO_2_HEALTH = 1000.f;
    std::string const CASTLE_NO_2_FILE = "res/castles/CastleNo2.png";
    size_t const CASTLE_NO_2_COST = 500.f;

    enum CastleType {
        CastleTypeNo1 = 1
        , CastleTypeNo2
    };

    class CastleObject
        : public StaticObject, public AliveObject
    {
    public:
        CastleObject();
        CastleObject(float maxHealth, std::string const& fileName, size_t cost = 0);
        CastleObject(CastleType type);

        virtual ~CastleObject() = default;

        virtual void Update(Game* const scene) override;

        size_t GetCost() const;
        static size_t GetClassCost(CastleType type);
        static std::string GetClassFile(CastleType type);

    protected:
        virtual void OnRightAlignmentUpdate_() override;

    private:
        size_t cost_;

        static float GetClassHealth_(CastleType type);
    };

}

#endif // __CASTLE_OBJECT_INCLUDED__