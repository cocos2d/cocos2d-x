#pragma once

#include "../Buffer.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class BufferMTL : public Buffer
{
public:
    BufferMTL(id<MTLDevice> mtlDevice, size_t size, BufferType type, BufferUsage usage);
    ~BufferMTL();
    
    virtual void updateData(void* data, size_t offset, size_t size) override;
    
    inline id<MTLBuffer> getMTLBuffer() const { return _mtlBuffer; }
    
private:
    id<MTLBuffer> _mtlBuffer = nil;
};

CC_BACKEND_END
