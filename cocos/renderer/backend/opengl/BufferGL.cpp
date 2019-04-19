#include "BufferGL.h"
#include <cassert>
#include "base/ccMacros.h"
#include "renderer/backend/BufferManager.h"
CC_BACKEND_BEGIN

BufferGL::BufferGL(unsigned int size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    glGenBuffers(1, &_buffer);
    BufferManager::addBuffer(this);
}

BufferGL::~BufferGL()
{
    if (_buffer)
        glDeleteBuffers(1, &_buffer);

    BufferManager::removeBuffer(this);
}

void BufferGL::reCreateBuffer()
{
    if (_buffer)
        glDeleteBuffers(1, &_buffer);

    glGenBuffers(1, &_buffer);
    char* zeros = new (std::nothrow) char[_bufferAllocated];
    updateData(zeros, _bufferAllocated);
    CC_SAFE_DELETE_ARRAY(zeros);
}

void BufferGL::updateData(void* data, unsigned int size)
{
    assert(size && size <= _size);
    
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
        _bufferAllocated = size;
    }
}

void BufferGL::updateSubData(void* data, unsigned int offset, unsigned int size)
{

    CCASSERT(_bufferAllocated != 0, "updateData should be invoke before updateSubData");
    CCASSERT(offset + size <= _bufferAllocated, "buffer size overflow");
 
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
