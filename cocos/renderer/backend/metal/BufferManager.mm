#include "BufferManager.h"
#include "BufferMTL.h"

CC_BACKEND_BEGIN

std::vector<BufferMTL*> BufferManager::_buffers;

void BufferManager::addBuffer(BufferMTL* buffer)
{
    _buffers.push_back(buffer);
}

void BufferManager::removeBuffer(BufferMTL* buffer)
{
    auto iter = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (_buffers.end() != iter)
        _buffers.erase(iter);
}

void BufferManager::beginFrame()
{
    for (auto& buffer : _buffers)
        buffer->beginFrame();
}

CC_BACKEND_END
