#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

class Buffer : public cocos2d::Ref
{
public:
    virtual void updateData(void* data, size_t size) = 0;
    virtual void updateSubData(void* data, size_t offset, size_t size) = 0;
    
protected:
    Buffer(size_t size, BufferType type, BufferUsage usage)
    : _size(size)
    , _type(type)
    , _usage(usage)
    {}
    
    virtual ~Buffer() = default;
    
    BufferUsage _usage = BufferUsage::READ;
    BufferType _type = BufferType::VERTEX;
    size_t _size = 0;
};

CC_BACKEND_END
