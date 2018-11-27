#include "BufferMTL.h"

CC_BACKEND_BEGIN

BufferMTL::BufferMTL(id<MTLDevice> mtlDevice, uint32_t size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    _mtlBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
}

BufferMTL::~BufferMTL()
{
    [_mtlBuffer release];
}

void BufferMTL::updateData(void* data, uint32_t size)
{
    memcpy(_mtlBuffer.contents, data, size);
}

CC_BACKEND_END
