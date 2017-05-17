#ifndef __DYNAMIC_OBJECT_INCLUDED__
#define __DYNAMIC_OBJECT_INCLUDED__

#include "GameObject.h"

namespace aad {

    class DynamicObject abstract
        : public GameObject
    {
    public:
        DynamicObject();
        DynamicObject(float x, float y, float hSpeed, float vSpeed, cocos2d::Sprite* sprite = nullptr);
        DynamicObject(float x, float y, float hSpeed, float vSpeed, std::string const& fileName);

        virtual ~DynamicObject() = default;

        virtual void Update(Game* const scene) override;

        float GetHSpeed() const;
        float GetVSpeed() const;

        void SetHSpeed(float speed);
        void SetVSpeed(float speed);
    protected:
        float hSpeed_;
        float vSpeed_;
    };

}

#endif // __DYNAMIC_OBJECT_INCLUDED__