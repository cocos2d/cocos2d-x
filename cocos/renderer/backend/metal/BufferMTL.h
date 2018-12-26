#pragma once

#include "../Buffer.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class BufferMTL : public Buffer
{
public:
    BufferMTL(id<MTLDevice> mtlDevice, unsigned int size, BufferType type, BufferUsage usage);
    ~BufferMTL();
    
    virtual void updateData(void* data, unsigned int size) override;
    virtual void updateSubData(void* data, unsigned int offset, unsigned int size) override;
    
    inline id<MTLBuffer> getMTLBuffer() const { return _mtlBuffer; }
    
private:
    id<MTLBuffer> _mtlBuffer = nil;
};

CC_BACKEND_END
