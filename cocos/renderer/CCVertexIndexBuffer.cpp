
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

GLArrayBuffer::GLArrayBuffer()
    : _vbo(0)
    , _vboSize(0)
    , _elementSize(0)
    , _elementCount(0)
    , _elements(nullptr)
    , _capacity(0)
{}

GLArrayBuffer::~GLArrayBuffer()
{
    if (glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
    
    CC_SAFE_FREE(_elements);
}

bool GLArrayBuffer::init(int elementSize, int capacity, ArrayType arrayType, ArrayMode arrayMode)
{
    if(0 == elementSize || 0 == capacity)
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
    
    _capacity     = capacity;
    _elementSize  = elementSize;
    _elementCount = 0;
    
    if (hasClient())
        ensureCapacity(_capacity * getElementSize());
    
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
    
    if (count + begin > _capacity)
    {
        ensureCapacity(count + begin);
    }
    
    if (0 == _vbo && hasNative())
    {
        glGenBuffers(1, &_vbo);
    }
    
    if (hasClient())
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        memcpy((void*)p, elements, count * _elementSize);
    
        _elementCount += count;
        _dirty = true;
    }
    
    CCLOG("GLArrayBuffer::insert : begin(%u) count(%u)\n", begin, count);

    if (false == defer)
        commit(count, begin);
        
    return true;
}

void GLArrayBuffer::commit(unsigned count, unsigned begin)
{
    if (count == 0)
        count = _elementCount;
    
    CHECK_GL_ERROR_DEBUG();
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    CHECK_GL_ERROR_DEBUG();
    
    const auto size = getSize();
    if (size > _vboSize)
    {
        _vboSize = size;
        glBufferData(GL_ARRAY_BUFFER, size, (void*)_elements, _opaqueDrawMode);
        CHECK_GL_ERROR_DEBUG();
    }
    else
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        glBufferSubData(GL_ARRAY_BUFFER, begin * _elementSize, count * _elementSize, (void*)p);
        CHECK_GL_ERROR_DEBUG();
    }
    
    setDirty(false);
    
    CCLOG("GLArrayBuffer::commit : begin(%u) count(%u)\n", begin, count);
        
    CHECK_GL_ERROR_DEBUG();
}

unsigned GLArrayBuffer::append(void* source, unsigned size, unsigned elements)
{
    CCASSERT(hasClient(), "Can only append data to arrays that have client buffers");
    updateElements(source, elements, _elementCount, true);
    return getSize();
}

void GLArrayBuffer::clear()
{
    _elementCount = 0;
    _dirty = false;
}

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

void GLArrayBuffer::ensureCapacity(unsigned capacity)
{
    if (hasClient())
    {
        _capacity = capacity;
        _elements = realloc(_elements, capacity);
    }
}

NS_CC_END
