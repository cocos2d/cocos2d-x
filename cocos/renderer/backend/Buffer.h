#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

class Buffer : public cocos2d::Ref
{
public:
    virtual void updateData(void* data, uint32_t size) = 0;
    
protected:
    Buffer(uint32_t size, BufferType type, BufferUsage usage)
    : _size(size)
    , _type(type)
    , _usage(usage)
    {}
    
    virtual ~Buffer() = default;
    
    BufferUsage _usage = BufferUsage::READ;
    BufferType _type = BufferType::VERTEX;
    uint32_t _size = 0;
};

CC_BACKEND_END
