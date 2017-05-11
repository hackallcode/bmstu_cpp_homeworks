#ifndef __BASIC_BLOCK_OBJECT_INCLUDED__
#define __BASIC_BLOCK_OBJECT_INCLUDED__

#include "BlockObject.h"

namespace AttackAndDefend {

    class BasicBlockObject
        : public BlockObject
    {
    public:
        BasicBlockObject(float x, float y);

        virtual ~BasicBlockObject() = default;
    };

}

#endif // __BASIC_BLOCK_OBJECT_INCLUDED__