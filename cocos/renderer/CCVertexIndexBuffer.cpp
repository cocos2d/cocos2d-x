
/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "base/CCConfiguration.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#define SUPPORT_EVENT_RENDERER_RECREATED
#endif

GLArrayBuffer::GLArrayBuffer()
    : _vbo(0)
    , _vao(0)
    , _elementSize(0)
    , _elementCount(0)
    , _elements(nullptr)
{
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    _recreateEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, [this](EventCustom* event){this->recreate();};);
#endif
}

GLArrayBuffer::~GLArrayBuffer()
{
    if (glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }

    if (glIsBuffer(_vao))
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
    
    CC_SAFE_FREE(_elements);
    
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool GLArrayBuffer::init(int elementSize, int elementCount, ArrayType arrayType, ArrayMode arrayMode)
{
    if(0 == elementSize || 0 == elementCount)
        return false;
    
    _arrayType = arrayType;
    _arrayMode = arrayMode;
    
    switch (_arrayMode)
    {
    case ArrayMode::Immutable:
        _opaqueDrawMode = GL_STATIC_DRAW;
        break;
    case ArrayMode::LongLived:
        _opaqueDrawMode = GL_DYNAMIC_DRAW;
        break;
    case ArrayMode::Dynamic:
        _opaqueDrawMode = GL_STREAM_DRAW;
        break;
    default:
        CCASSERT(false, "invalid ArrayMode");
        return false;
    }
        
    _elementSize  = elementSize;
    _elementCount = elementCount;
    
    if (hasClient())
        ensureCapacity(getSize());
    
    if (hasNative())
    {
        if (hasVAO() && Configuration::getInstance()->supportsShareableVAO())
        {
            glGenVertexArrays(1, &_vao);
            GL::bindVAO(_vao);
        }

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, getSize(), nullptr, _opaqueDrawMode);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    return true;
}

bool GLArrayBuffer::updateElements(const void* elements, int count, int begin, bool defer)
{
    if (count <= 0 || nullptr == elements)
        return false;
    
    if (begin < 0)
    {
        CCLOGERROR("Update vertices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if (count + begin > _elementCount)
    {
        CCLOGERROR("updated vertices exceed the max size of vertex buffer, will set count to _vertexNumber-begin");
        count = _elementCount - begin;
    }
    
    if (_elements && hasClient())
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        memcpy((void*)p, elements, count * _elementSize);
    }
    
    if (false == defer)
    {
        update(count, begin);
    }
    
    return true;
}

bool GLArrayBuffer::update(int count, int begin)
{
    if (count < 0)
        return false;
    
    if (count == 0)
        count = _elementCount;
    
    if (begin < 0)
    {
        CCLOGERROR("Update vertices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if (count + begin > _elementCount)
    {
        CCLOGERROR("updated vertices exceed the max size of vertex buffer, will set count to _vertexNumber-begin");
        count = _elementCount - begin;
    }

    if (hasClient())
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, begin * _elementSize, count * _elementSize, (void*)p);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        CHECK_GL_ERROR_DEBUG();
    }
    
    return true;
}

size_t GLArrayBuffer::append(void* source, size_t size, size_t elements)
{
    CCASSERT(hasClient(), "Can only append data to arrays that have client buffers");
    
    auto currentSize = getSize();
    ensureCapacity(currentSize + size);
    
    intptr_t p = (intptr_t)_elements + currentSize;
    memcpy((void*)p, source, size * elements);
    
    _elementCount += elements;
    _dirty = true;
    
    return getSize();
}

void GLArrayBuffer::clear()
{
    _elementCount = 0;
    _dirty = false;
}

#ifdef SUPPORT_EVENT_RENDERER_RECREATED
void GLArrayBuffer::recreate() const
{
    glGenBuffers(1, (GLuint*)&_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    if (_elements)
    {
        glBufferData(GL_ARRAY_BUFFER, _elementSize * _elementCount, _elements, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if(!glIsBuffer(_vbo))
        {
            CCLOGERROR("Renderer::recreate() : recreate VertexBuffer Error");
        }
    }
}
#endif

void GLArrayBuffer::ensureCapacity(size_t capacity)
{
    if (hasClient())
    {
        _elements = realloc(_elements, capacity);
    }
}

NS_CC_END
