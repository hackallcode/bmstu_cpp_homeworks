#include "StaticObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

StaticObject::StaticObject()
    : GameObject()
{}

StaticObject::StaticObject(float x, float y, cocos2d::Sprite* sprite)
    : GameObject(x, y, sprite)
{}

StaticObject::StaticObject(float x, float y, std::string const& fileName)
    : GameObject(x, y, fileName)
{}