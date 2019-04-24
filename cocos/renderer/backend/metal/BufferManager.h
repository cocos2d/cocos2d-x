#pragma once

#include <vector>
#include "../Macros.h"

CC_BACKEND_BEGIN

class BufferMTL;

class BufferManager
{
public:
    static void addBuffer(BufferMTL* buffer);
    static void removeBuffer(BufferMTL* buffer);
    static void beginFrame();

private:
    static std::vector<BufferMTL*> _buffers;
};

CC_BACKEND_END
