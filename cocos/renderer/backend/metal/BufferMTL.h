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
    
    id<MTLBuffer> getMTLBuffer() const;
    void beginFrame();
    
private:
    void updateIndex();

    id<MTLBuffer> _mtlBuffer = nil;
    NSMutableArray* _dynamicDataBuffers = nil;
    int _currentFrameIndex = 0;
    bool _indexUpdated = false;
};

CC_BACKEND_END
