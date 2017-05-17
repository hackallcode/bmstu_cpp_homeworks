#include "StaticObject.h"
#include "GameScene.h"

aad::StaticObject::StaticObject()
    : GameObject()
{}

aad::StaticObject::StaticObject(float x, float y, cocos2d::Sprite* sprite)
    : GameObject(x, y, sprite)
{}

aad::StaticObject::StaticObject(float x, float y, std::string const& fileName)
    : GameObject(x, y, fileName)
{}