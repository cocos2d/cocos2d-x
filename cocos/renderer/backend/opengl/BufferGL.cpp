/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "BufferGL.h"
#include <cassert>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"

CC_BACKEND_BEGIN

namespace {
    GLenum toGLUsage(const BufferUsage& usage)
    {
        switch (usage)
        {
            case BufferUsage::STATIC:
                return GL_STATIC_DRAW;
            case BufferUsage::DYNAMIC:
                return GL_DYNAMIC_DRAW;
            default:
                return GL_DYNAMIC_DRAW;
        }
    }
}

BufferGL::BufferGL(std::size_t size, BufferType type, BufferUsage usage)
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

void BufferGL::usingDefaultStoredData(bool needDefaultStoredData)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _needDefaultStoredData = needDefaultStoredData;
#endif
}

#if CC_ENABLE_CACHE_TEXTURE_DATA
void BufferGL::reloadBuffer()
{
    glGenBuffers(1, &_buffer);

    if(!_needDefaultStoredData)
        return;

    _bufferAlreadyFilled = true;
    updateData(_data, _bufferAllocated);
}

void BufferGL::fillBuffer(void* data, std::size_t offset, std::size_t size)
{
    if(_bufferAlreadyFilled || !_needDefaultStoredData || BufferUsage::STATIC != _usage)
        return;

    if(_data == nullptr)
    {
        _data = new (std::nothrow) char[_bufferAllocated];
    }

    memcpy(_data + offset, data, size);

}
#endif

void BufferGL::updateData(void* data, std::size_t size)
{
    assert(size && size <= _size);
    
    if (_buffer)
    {
        if (BufferType::VERTEX == _type)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _buffer);
            glBufferData(GL_ARRAY_BUFFER, size, data, toGLUsage(_usage));
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, toGLUsage(_usage));
        }
        CHECK_GL_ERROR_DEBUG();
        _bufferAllocated = size;

#if CC_ENABLE_CACHE_TEXTURE_DATA
        fillBuffer(data, 0, size);
#endif
    }
}

void BufferGL::updateSubData(void* data, std::size_t offset, std::size_t size)
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
