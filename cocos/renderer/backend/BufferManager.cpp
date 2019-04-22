#include "BufferManager.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformConfig.h"
#include "renderer/backend/Buffer.h"

CC_BACKEND_BEGIN

std::vector<BufferInfo> BufferManager::_buffers;

void BufferManager::addBuffer(Buffer* buffer)
{
    BufferInfo bufferInfo = {buffer};
    _buffers.push_back(std::move(bufferInfo));
}

void BufferManager::removeBuffer(Buffer* buffer)
{
    for(auto iter = _buffers.begin(); iter != _buffers.end(); ++iter)
    {
        if(iter->buffer == buffer)
        {
            _buffers.erase(iter);
            break;
        }
    }
}

void BufferManager::reloadAllBuffers()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    for(auto iter : _buffers)
    {
        iter.buffer->reloadBuffer(iter.data.data(), iter.data.size());
    }
#endif
}

void BufferManager::addBufferData(cocos2d::backend::Buffer *buffer, void *data,
                                  unsigned int dataLen)
{
    for(auto iter = _buffers.begin(); iter != _buffers.end(); ++iter)
    {
        if(iter->buffer == buffer)
        {
            iter->data.assign((char*)data, (char*)data + dataLen);
            break;
        }
    }
}

void BufferManager::beginFrame()
{
#ifdef CC_USE_METAL
    for (auto& iter : _buffers)
        iter.buffer->beginFrame();
#endif
}

CC_BACKEND_END
