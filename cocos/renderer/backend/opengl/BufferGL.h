#pragma once

#include "../Buffer.h"

#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class BufferGL : public Buffer
{
public:
    BufferGL(uint32_t size, BufferType type, BufferUsage usage);
    ~BufferGL();
    
    virtual void updateData(void* data, size_t offset, size_t size) override;
    inline GLuint getHandler() const { return _buffer; }
    
private:
    GLuint _buffer = 0;
};

CC_BACKEND_END
