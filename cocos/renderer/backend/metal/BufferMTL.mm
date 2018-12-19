#include "BufferMTL.h"

CC_BACKEND_BEGIN

BufferMTL::BufferMTL(id<MTLDevice> mtlDevice, size_t size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    _mtlBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
}

BufferMTL::~BufferMTL()
{
    [_mtlBuffer release];
}

void BufferMTL::updateData(void* data, size_t size)
{
    assert(size <= _size);
    memcpy((char*)_mtlBuffer.contents, data, size);
}

void BufferMTL::updateSubData(void* data, size_t offset, size_t size)
{
    assert(offset + size <= _size);
    memcpy((char*)_mtlBuffer.contents + offset, data, size);
}

CC_BACKEND_END
