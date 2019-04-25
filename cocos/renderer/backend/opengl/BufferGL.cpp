#include "BufferGL.h"
#include <cassert>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"

CC_BACKEND_BEGIN

BufferGL::BufferGL(unsigned int size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    glGenBuffers(1, &_buffer);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        this->reloadBuffer();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

BufferGL::~BufferGL()
{
    if (_buffer)
        glDeleteBuffers(1, &_buffer);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    CC_SAFE_DELETE_ARRAY(_data);
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

#if CC_ENABLE_CACHE_TEXTURE_DATA
void BufferGL::reloadBuffer()
{
    _bufferAlreadyFilled = true;
    glGenBuffers(1, &_buffer);
    updateData(_data, _bufferAllocated);
}

void BufferGL::fillBuffer(void* data, unsigned int offset, unsigned int size)
{
    if(_bufferAlreadyFilled)
        return;

    if(_data == nullptr)
    {
        _data = new (std::nothrow) char[_bufferAllocated];
    }

    if(BufferUsage::STATIC ==  _usage)
    {
        memcpy(_data + offset, data, size);
    }
}
#endif

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

#if CC_ENABLE_CACHE_TEXTURE_DATA
        fillBuffer(data, 0, size);
#endif
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

#if CC_ENABLE_CACHE_TEXTURE_DATA
        fillBuffer(data, offset, size);
#endif
        CHECK_GL_ERROR_DEBUG();
    }
}

CC_BACKEND_END
