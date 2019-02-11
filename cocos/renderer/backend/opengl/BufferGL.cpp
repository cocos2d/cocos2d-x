#include "BufferGL.h"
#include <cassert>
#include "base/ccMacros.h"
CC_BACKEND_BEGIN

BufferGL::BufferGL(unsigned int size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    glGenBuffers(1, &_buffer);
}

BufferGL::~BufferGL()
{
    if (_buffer)
        glDeleteBuffers(1, &_buffer);
}

void BufferGL::updateData(void* data, unsigned int size)
{
    assert(size);
    
    if (_buffer)
    {
        if (BufferType::VERTEX == _type)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _buffer);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }
        CHECK_GL_ERROR_DEBUG();
        _bufferAllocated = true;
    }
}

void BufferGL::updateSubData(void* data, unsigned int offset, unsigned int size)
{
    assert(offset + size <= _size);
    
    //invoke updateData if buffer is not allocated
    if (!_bufferAllocated)
    {
        CCASSERT(offset == 0, "offset should be zero when allocate buffer");
        updateData(data, size);
        return;
    }

    if (_buffer)
    {
        CHECK_GL_ERROR_DEBUG();
        if (BufferType::VERTEX == _type)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _buffer);
            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        }
        CHECK_GL_ERROR_DEBUG();
    }
}

CC_BACKEND_END
