#include "BufferGL.h"

CC_BACKEND_BEGIN

BufferGL::BufferGL(uint32_t size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    glGenBuffers(1, &_buffer);
}

BufferGL::~BufferGL()
{
    if (_buffer)
        glDeleteBuffers(1, &_buffer);
}

void BufferGL::updateData(void* data, size_t offset, size_t size)
{
    assert(offset + size <= _size);
    
    if (_buffer)
    {
        if (BufferType::VERTEX == _type)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _buffer);
            if (offset)
            {
                glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            }
            else
            {
                glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            }
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
            if (offset)
            {
                glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            }
            else
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            }
        }
    }
}

CC_BACKEND_END
