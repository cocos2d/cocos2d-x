#include "BufferManager.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformConfig.h"
#include "renderer/backend/Buffer.h"

CC_BACKEND_BEGIN

std::vector<Buffer*> BufferManager::_buffers;

void BufferManager::addBuffer(Buffer* buffer)
{
    _buffers.push_back(buffer);
}

void BufferManager::removeBuffer(Buffer* buffer)
{
    auto iter = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (_buffers.end() != iter)
        _buffers.erase(iter);
}

void BufferManager::reloadAllBuffers()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    for(auto buffer : _buffers)
    {
        buffer->reCreateBuffer();
    }
#endif
}

void BufferManager::beginFrame()
{
#ifdef CC_USE_METAL
    for (auto& buffer : _buffers)
        buffer->beginFrame();
#endif
}

CC_BACKEND_END
