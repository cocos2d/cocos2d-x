#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

namespace cocos2d {
    class MeshVertexData;
    class MeshIndexData;
}

CC_BACKEND_BEGIN

class Buffer : public cocos2d::Ref
{
public:
    virtual void updateData(void* data, unsigned int size) = 0;
    virtual void updateSubData(void* data, unsigned int offset, unsigned int size) = 0;

    /*
     * By default, static buffer data will automatically stored when it comes to foreground.
     * This function is used to indicate whether external data needs to be used to update the buffer instead of using the default stored data.
     */
    virtual void usingDefaultStoredData(bool needDefaultStoredData) = 0;

    unsigned int getSize() const { return _size; }

protected:
    Buffer(unsigned int size, BufferType type, BufferUsage usage)
    : _usage(usage)
    , _type(type)
    , _size(size)
    {}
    
    virtual ~Buffer() = default;
    
    BufferUsage _usage = BufferUsage::DYNAMIC;
    BufferType _type = BufferType::VERTEX;
    unsigned int _size = 0;
};

CC_BACKEND_END
