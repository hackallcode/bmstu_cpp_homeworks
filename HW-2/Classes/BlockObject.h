#ifndef __BLOCK_OBJECT_INCLUDED__
#define __BLOCK_OBJECT_INCLUDED__

#include "StaticObject.h"

namespace aad {

    class BlockObject abstract
        : public StaticObject
    {
    public:
        BlockObject();
        BlockObject(float x, float y, std::string const& fileName);

        virtual ~BlockObject() = default;
    };

}

#endif // __BLOCK_OBJECT_INCLUDED__