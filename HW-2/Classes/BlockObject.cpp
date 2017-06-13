#include "BlockObject.h"
#include "GameScene.h"

aad::BlockObject::BlockObject()
    : StaticObject()
{}

aad::BlockObject::BlockObject(float x, float y, std::string const& fileName)
    : StaticObject(x, y, fileName)
{}

aad::BlockObject::BlockObject(float x, float y, BlockType type)
    : BlockObject(x, y, BlockObject::GetClassFile_(type))
{}

std::string aad::BlockObject::GetClassFile_(BlockType type)
{
    switch (type)
    {
    case aad::BasicBlockType:
        return BASIC_BLOCK_FILE;
    case aad::GrassBlockType:
        return GRASS_BLOCK_FILE;
    default:
        return UNKNOWN_BLOCK_FILE;
    }
}
