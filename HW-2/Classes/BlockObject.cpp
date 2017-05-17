#include "BlockObject.h"
#include "GameScene.h"

aad::BlockObject::BlockObject()
    : StaticObject()
{}

aad::BlockObject::BlockObject(float x, float y, std::string const& fileName)
    : StaticObject(x, y, fileName)
{}