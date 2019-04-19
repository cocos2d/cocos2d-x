#pragma once

#include <vector>
#include "Macros.h"

CC_BACKEND_BEGIN

class Buffer;

class BufferManager
{
public:
    static void addBuffer(Buffer* buffer);
    static void removeBuffer(Buffer* buffer);
    static void reloadAllBuffers();
    static void beginFrame();

private:
    static std::vector<Buffer*> _buffers;
    
};

CC_BACKEND_END
