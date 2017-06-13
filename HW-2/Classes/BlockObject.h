#ifndef __BLOCK_OBJECT_INCLUDED__
#define __BLOCK_OBJECT_INCLUDED__

#include <string>
#include "StaticObject.h"

namespace aad {

    std::string const UNKNOWN_BLOCK_FILE = "res/blocks/UnknownBlock.png";
    std::string const BASIC_BLOCK_FILE = "res/blocks/BasicBlock.png";
    std::string const GRASS_BLOCK_FILE = "res/blocks/GrassBlock.png";

    enum BlockType {
        BasicBlockType = 1
        , GrassBlockType
    };

    class BlockObject
        : public StaticObject
    {
    public:
        BlockObject();
        BlockObject(float x, float y, std::string const& fileName);
        BlockObject(float x, float y, BlockType type);

        virtual ~BlockObject() = default;

    private:
        static std::string GetClassFile_(BlockType type);
    };

}

#endif // __BLOCK_OBJECT_INCLUDED__