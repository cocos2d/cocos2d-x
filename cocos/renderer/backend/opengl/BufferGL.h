#pragma once

#include "../Buffer.h"

#include "platform/CCGL.h"

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
    GLuint _buffer = 0;
};

CC_BACKEND_END
