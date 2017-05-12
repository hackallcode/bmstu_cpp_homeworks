#ifndef __GRASS_BLOCK_OBJECT_INCLUDED__
#define __GRASS_BLOCK_OBJECT_INCLUDED__

#include "BlockObject.h"

namespace AttackAndDefend {

    class GrassBlockObject
        : public BlockObject
    {
    public:
        GrassBlockObject(float x, float y);

        virtual ~GrassBlockObject() = default;
    };

}

#endif // __GRASS_BLOCK_OBJECT_INCLUDED__