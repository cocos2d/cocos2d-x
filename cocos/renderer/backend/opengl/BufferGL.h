#pragma once

#include "../Buffer.h"
#include "platform/CCGL.h"
#include "base/CCEventListenerCustom.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL : public Buffer
{
public:
    BufferGL(unsigned int size, BufferType type, BufferUsage usage);
    ~BufferGL();
    
    virtual void updateData(void* data, unsigned int size) override;
    virtual void updateSubData(void* data, unsigned int offset, unsigned int size) override;
    
    inline GLuint getHandler() const { return _buffer; }

private:
    void reloadBuffer();

    GLuint _buffer = 0;
    unsigned int _bufferAllocated = 0;
    std::vector<char> _data;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundListener = nullptr;
#endif
};

CC_BACKEND_END
