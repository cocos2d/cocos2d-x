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
    
    unsigned int getSize() const { return _size; }

protected:
    Buffer(unsigned int size, BufferType type, BufferUsage usage)
    : _usage(usage)
    , _type(type)
    , _size(size)
    {}
    
    virtual ~Buffer() = default;

    //using external data to reload buffer when it comes to foreground
    virtual void reloadBufferData(void* data, unsigned int size) = 0;

    //true means reload data ouside the buffer, otherwise reload data from the inside of the buffer.
    virtual void needReloadExternal(bool needReloadExternal) = 0;
    
    BufferUsage _usage = BufferUsage::DYNAMIC;
    BufferType _type = BufferType::VERTEX;
    unsigned int _size = 0;

    friend class cocos2d::MeshVertexData;
    friend class cocos2d::MeshIndexData;
};

CC_BACKEND_END
