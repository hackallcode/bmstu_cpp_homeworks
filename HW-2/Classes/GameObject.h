#ifndef __GAME_OBJECT_INCLUDED__
#define __GAME_OBJECT_INCLUDED__

#include "cocos2d.h"
#include <string>

namespace aad {

    class Game;

    class GameObject abstract
    {
    public:
        GameObject();
        GameObject(float x, float y, cocos2d::Sprite* sprite = nullptr);
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