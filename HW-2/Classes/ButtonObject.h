#ifndef __BUTTON_OBJECT_INCLUDED__
#define __BUTTON_OBJECT_INCLUDED__

#include <string>
#include "StaticObject.h"
#include "AttackerObject.h"
#include "CastleObject.h"

namespace aad {

    float const BUTTON_X_START = 20.f;
    float const BUTTON_Y_START = 830.f;
    float const BUTTON_MARGIN = 20.f;

    float const BUTTON_PADDING = 10.f;
    float const BUTTON_FONT_SIZE = 45.f;
    std::string const BUTTON_BACKGROUND_FILE = "res/buttons/background.png";
    std::string const LOCK_BUTTON_FILE = "res/buttons/lock.png";
    
    size_t const UNKNOWN_BUTTON_COST = 0;
    std::string const UNKNOWN_BUTTON_FILE = "res/buttons/unknown.png";

    size_t const HEALTH_BUTTON_COST = 10;
    std::string const HEALTH_BUTTON_FILE = "res/buttons/health.png";

    size_t const ARMOR_BUTTON_COST = 10;
    std::string const ARMOR_BUTTON_FILE = "res/buttons/shield.png";

    enum ButtonType {
          HealthButton = 1
        , ArmorButton
    };

    class ButtonObject
        : public StaticObject
    {
    public:
        ButtonObject();
        ButtonObject(float x, float y, std::string fileName, std::string topLabel = std::string(), std::string bottomLabel = std::string(), bool isLocked = false);
        ButtonObject(float x, float y, ButtonType type, std::string key = std::string(), bool isLocked = false);
        ButtonObject(float x, float y, AttackerType type, std::string key = std::string(), bool isLocked = false);
        ButtonObject(float x, float y, CastleType type, std::string key = std::string(), bool isLocked = false);

        virtual ~ButtonObject() = default;

        void Lock();
        void Unlock();

        std::string GetTopLabel() const;
        std::string GetBottomLabel() const;

    protected:
        virtual void OnRightAlignmentUpdate_() override;

    private:
        bool isLocked_;
        cocos2d::Sprite* faceSprite_;
        cocos2d::Sprite* lockSprite_;
        cocos2d::CCLabelTTF* topLabel_;
        cocos2d::CCLabelTTF* bottomLabel_;

        static size_t GetClassCost_(ButtonType type);
        static std::string GetClassFile_(ButtonType type);
    };

}

#endif // __BUTTON_OBJECT_INCLUDED__