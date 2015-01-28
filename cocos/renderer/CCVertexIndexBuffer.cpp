
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
    , _target(0)
    , _elementCount(0)
    , _elements(nullptr)
    , _elementSize(0)
    , _capacity(0)
    , _arrayType(ArrayType::Invalid)
    , _arrayMode(ArrayMode::Invalid)
    , _usage(0)
    , _dirty(true)
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

bool GLArrayBuffer::init(int elementSize, int maxElements, ArrayType arrayType, ArrayMode arrayMode)
{
    if(0 == elementSize || 0 == maxElements)
        return false;
    
    _arrayType = arrayType;
    _arrayMode = arrayMode;
    _target = nativeBindTarget();
    
    switch (_arrayMode)
    {
    case ArrayMode::Immutable:
        _usage = GL_STATIC_DRAW;
        break;
    case ArrayMode::LongLived:
        _usage = GL_DYNAMIC_DRAW;
        break;
    case ArrayMode::Dynamic:
        _usage = GL_STREAM_DRAW;
        break;
    default:
        CCASSERT(false, "invalid ArrayMode");
        return false;
    }
    
    _elementSize  = elementSize;
    _elementCount = 0;
    
    setCapacity(maxElements * getElementSize());
    
    return true;
}

bool GLArrayBuffer::updateElements(const void* elements, unsigned count, unsigned begin, bool defer)
{
    if (0 == count || nullptr == elements)
        return false;
    
    setDirty(true);

    // if we have no client buffer, then commit to native immediately.
    if (false == hasClient())
        defer = false;

    auto needed = getElementSize() * (count + begin);
    if (needed > _capacity)
        setCapacity(needed);
    
    if (hasClient())
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        memcpy((void*)p, elements, count * _elementSize);
    }
    
    _elementCount += count;

    if (false == defer && hasNative())
        bindAndCommit(elements, count, begin);

    return true;
}

void GLArrayBuffer::bindAndCommit(const void* elements, unsigned count, unsigned begin)
{
    if (_vbo)
        GL::bindVBO(_target, _vbo);

    if (false == isDirty() || false == hasNative())
        return;
    
    if (nullptr == elements)
        elements = _elements;
    
    if (0 == _vbo)
    {
        glGenBuffers(1, &_vbo);
        _vboSize = _capacity;
        GL::bindVBO(_target, _vbo);
        glBufferData(_target, _capacity, elements, _usage);
    }
    else
    {
        const auto size = getSize();
        if (size > _vboSize)
        {
            _vboSize = size;
            glBufferData(_target, size, elements, _usage);
            CHECK_GL_ERROR_DEBUG();
        }
        else
        {
            if (count == 0)
                count = _elementCount;
            
            intptr_t p = (intptr_t)elements + begin * _elementSize;
            glBufferSubData(_target, begin * _elementSize, count * _elementSize, (void*)p);
            CHECK_GL_ERROR_DEBUG();
        }
    }
    
    CHECK_GL_ERROR_DEBUG();

    setDirty(false);
}

unsigned GLArrayBuffer::append(void* source, unsigned elements)
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
    if (glIsBuffer(_vbo))
        glDeleteBuffers(1, &_vbo);
    glGenBuffers(1, (GLuint*)&_vbo);
    glBindBuffer(_target, _vbo);
    if (_elements)
    {
        glBufferData(_target, _elementSize * _elementCount, _elements, GL_STATIC_DRAW);
        glBindBuffer(_target, 0);
        if(!glIsBuffer(_vbo))
        {
            CCLOGERROR("Renderer::recreate() : recreate VertexBuffer Error");
        }
    }
}

void GLArrayBuffer::setCapacity(unsigned capacity)
{
    _capacity = capacity;
    if (hasClient())
        _elements = realloc(_elements, capacity);
}

//
// Specializations for buffer OpenGL types
//

int VertexBuffer::nativeBindTarget() const
{
    return GL_ARRAY_BUFFER;
}

int IndexBuffer::nativeBindTarget() const
{
    return GL_ELEMENT_ARRAY_BUFFER;
}

NS_CC_END
