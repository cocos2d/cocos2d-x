#include "BufferMTL.h"
#include "../Macros.h"
#include "BufferManager.h"

CC_BACKEND_BEGIN

BufferMTL::BufferMTL(id<MTLDevice> mtlDevice, unsigned int size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
//    _mtlBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];

    int maxInflightBuffers = BufferUsage::DYNAMIC == usage ? MAX_INFLIGHT_BUFFER : 1;
    NSMutableArray *mutableDynamicDataBuffers = [NSMutableArray arrayWithCapacity:maxInflightBuffers];
    for (int i = 0; i < maxInflightBuffers; ++i)
    {
        // Create a new buffer with enough capacity to store one instance of the dynamic buffer data
        id <MTLBuffer> dynamicDataBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
        [mutableDynamicDataBuffers addObject:dynamicDataBuffer];
    }
    _dynamicDataBuffers = [mutableDynamicDataBuffers copy];

    _mtlBuffer = _dynamicDataBuffers[0];

    BufferManager::addBuffer(this);
}

BufferMTL::~BufferMTL()
{
    for (id<MTLBuffer> buffer in _dynamicDataBuffers)
        [buffer release];

    BufferManager::removeBuffer(this);
}

void BufferMTL::updateData(void* data, unsigned int size)
{
    assert(size <= _size);
    memcpy((uint8_t*)_mtlBuffer.contents, data, size);
}

void BufferMTL::updateSubData(void* data, unsigned int offset, unsigned int size)
{
    assert(offset + size <= _size);
    memcpy((uint8_t*)_mtlBuffer.contents + offset, data, size);
}

id<MTLBuffer> BufferMTL::getMTLBuffer() const
{
    return _mtlBuffer;
}

void BufferMTL::updateIndex()
{
    if (BufferUsage::DYNAMIC == _usage)
        _currentFrameIndex = (_currentFrameIndex + 1) % MAX_INFLIGHT_BUFFER;
    else
        _currentFrameIndex = 0;
        
    _mtlBuffer = _dynamicDataBuffers[_currentFrameIndex];
}

CC_BACKEND_END
