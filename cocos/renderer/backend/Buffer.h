#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

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
    
    BufferUsage _usage = BufferUsage::DYNAMIC;
    BufferType _type = BufferType::VERTEX;
    unsigned int _size = 0;
};

CC_BACKEND_END
