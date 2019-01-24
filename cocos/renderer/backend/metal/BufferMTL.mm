#include "BufferMTL.h"
#include "../Macros.h"
#include "BufferManager.h"

CC_BACKEND_BEGIN

BufferMTL::BufferMTL(id<MTLDevice> mtlDevice, unsigned int size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    if (BufferUsage::DYNAMIC == usage)
    {
        NSMutableArray *mutableDynamicDataBuffers = [NSMutableArray arrayWithCapacity:MAX_INFLIGHT_BUFFER];
        for (int i = 0; i < MAX_INFLIGHT_BUFFER; ++i)
        {
            // Create a new buffer with enough capacity to store one instance of the dynamic buffer data
            id <MTLBuffer> dynamicDataBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
            [mutableDynamicDataBuffers addObject:dynamicDataBuffer];
        }
        _dynamicDataBuffers = [mutableDynamicDataBuffers copy];

        _mtlBuffer = _dynamicDataBuffers[0];
        BufferManager::addBuffer(this);
    }
    else
    {
        _mtlBuffer = [mtlDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
    }
}

BufferMTL::~BufferMTL()
{
    if (BufferUsage::DYNAMIC == _usage)
    {
        for (id<MTLBuffer> buffer in _dynamicDataBuffers)
        [buffer release];

        BufferManager::removeBuffer(this);
    }
    else
    {
        [_mtlBuffer release];
    }
}

void BufferMTL::updateData(void* data, unsigned int size)
{
    assert(size <= _size);
    updateIndex();
    memcpy((uint8_t*)_mtlBuffer.contents, data, size);
}

void BufferMTL::updateSubData(void* data, unsigned int offset, unsigned int size)
{
    assert(offset + size <= _size);
    updateIndex();
    memcpy((uint8_t*)_mtlBuffer.contents + offset, data, size);
}

id<MTLBuffer> BufferMTL::getMTLBuffer() const
{
    return _mtlBuffer;
}

void BufferMTL::beginFrame()
{
    _indexUpdated = false;
}

void BufferMTL::updateIndex()
{
    if (BufferUsage::DYNAMIC == _usage && !_indexUpdated)
    {
        _currentFrameIndex = (_currentFrameIndex + 1) % MAX_INFLIGHT_BUFFER;
        _mtlBuffer = _dynamicDataBuffers[_currentFrameIndex];
        _indexUpdated = true;
    }
}

CC_BACKEND_END
