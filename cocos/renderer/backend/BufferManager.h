#pragma once

#include <vector>
#include "Macros.h"

CC_BACKEND_BEGIN

class Buffer;

struct BufferInfo
{
    Buffer* buffer;
    std::vector<char> data;
};

class BufferManager
{
public:
    static void addBuffer(Buffer* buffer);
    static void removeBuffer(Buffer* buffer);
    static void reloadAllBuffers();
    static void beginFrame();
    static void addBufferData(Buffer* buffer, void* data, unsigned int dataLen);

private:
    static std::vector<BufferInfo> _buffers;
};

CC_BACKEND_END
