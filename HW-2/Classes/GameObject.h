#ifndef __GAME_OBJECT_INCLUDED__
#define __GAME_OBJECT_INCLUDED__

#include "cocos2d.h"
#include <string>

namespace aad {

    const float ATTACKER_DISTANCE = 0;
    const float MARGIN_SIZE = 20.f;
    const float HEALTH_FONT_SIZE = 30.f;
    const float GROUND_HEIGHT = 80.f;    

    const float SIMPLE_ATTACKER_COST = 10.f;
    const float SIMPLE_ATTACKER_HEALTH = 10.f;
    const float SIMPLE_ATTACKER_POWER = 0.2f;
    const float SIMPLE_ATTACKER_SPEED = 1.5f;

    const float FIRST_ATTACKER_COST = 40.f;
    const float FIRST_ATTACKER_HEALTH = 70.f;
    const float FIRST_ATTACKER_POWER = 0.3f;
    const float FIRST_ATTACKER_SPEED = 3.f;

    const float SECOND_ATTACKER_COST = 90.f;
    const float SECOND_ATTACKER_HEALTH = 145.f;
    const float SECOND_ATTACKER_POWER = 0.45f;
    const float SECOND_ATTACKER_SPEED = 2.5f;

    const float THIRD_ATTACKER_COST = 150.f;
    const float THIRD_ATTACKER_HEALTH = 175.f;
    const float THIRD_ATTACKER_POWER = 0.68f;
    const float THIRD_ATTACKER_SPEED = 1.5f;

    class Game;

    class GameObject abstract
    {
    public:
        GameObject();
        GameObject(float x, float y, cocos2d::Sprite* sprite = nullptr); //TODO UPDATE
        GameObject(float x, float y, std::string const& fileName);

        virtual ~GameObject() = default;

        virtual void Update(Game* const scene);

        cocos2d::Sprite* GetSprite() const;
        float GetX() const;
        float GetY() const;
        float GetW() const;
        float GetH() const;
        bool IsRightAlignment() const;

        void SetSprite(cocos2d::Sprite* sprite);
        void SetLeftAlignment();
        void SetRightAlignment(float frameWidth);

    protected:
        void SetX_(float x);
        void SetY_(float y);
        void SetW_(float w);
        void SetH_(float h);
        
        virtual void PositionInit_();
        virtual void OnPositionUpdate_();
        virtual void OnXUpdate_();
        virtual void OnYUpdate_();
        virtual void OnWUpdate_();
        virtual void OnHUpdate_();
        virtual void OnRightAlignmentUpdate_();

    private:
        cocos2d::Sprite* sprite_;
        float x_, prevX_;
        float y_, prevY_;
        float w_, prevW_;
        float h_, prevH_;
        bool isRightAlignment_;
        float frameWidth_;

        void SetSpriteX_(float x);
        void SetSpriteY_(float y);
    };

}

#endif // __GAME_OBJECT_INCLUDED__