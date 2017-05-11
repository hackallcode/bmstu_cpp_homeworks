#include "BlockObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

BlockObject::BlockObject()
    : StaticObject()
{}

BlockObject::BlockObject(float x, float y, std::string const& fileName)
    : StaticObject(x, y, fileName)
{}