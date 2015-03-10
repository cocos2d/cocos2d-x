
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
#include "base/allocator/CCAllocatorMacros.h"

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
        GL::bindVBO(_target, 0);
        _vbo = 0;
    }
    
    CC_SAFE_FREE(_elements);
}

bool GLArrayBuffer::init(ssize_t elementSize, ssize_t maxElements, ArrayType arrayType, ArrayMode arrayMode, bool zero)
{
    CCASSERT(elementSize > 0 && elementSize < 512, "0 < maxElements size < 512");

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
    
    setCapacity(maxElements, zero);
    
    return true;
}

void GLArrayBuffer::setElements(const void* elements, ssize_t count, bool defer)
{
    setElementCount(count);
    updateElements(elements, count, 0, defer);
}

void GLArrayBuffer::updateElements(const void* elements, ssize_t count, ssize_t begin, bool defer)
{
    CCASSERT(begin >= 0, "Invalid being value");
    CCASSERT(count >= 0, "Invalid count value");

    CCASSERT(hasClient() || hasNative(), "Can only update elements if there is an attached buffer");
    
    if (0 == count)
        return;
    
    setDirty(true);

    // if we have no client buffer, then commit to native immediately.
    if (false == hasClient())
        defer = false;

    auto needed = count + begin;
    setCapacity(needed, false);
    
    if (hasClient())
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        if (elements)
            memmove((void*)p, elements, count * _elementSize);
        else
            memset((void*)p, 0, count * _elementSize);
    }

    // empty elements do not count towards element count, only capacity
    if (elements)
        _elementCount = begin + count > _elementCount ? begin + count : _elementCount;
    
    if (false == defer && elements && hasNative())
        bindAndCommit(elements, count, begin);
}

void GLArrayBuffer::insertElements(const void* elements, ssize_t count, ssize_t begin, bool defer)
{
    CCASSERT(hasClient(), "can only insert into a client buffer");
    // first see if we need to move any elements
    if (begin < getElementCount())
    {
        intptr_t dst = (intptr_t)_elements + begin + count;
        updateElements((void*)dst, count, begin, defer);
    }
    updateElements(elements, count, begin, defer);
}

void GLArrayBuffer::appendElements(const void* elements, ssize_t count, bool defer)
{
    CCASSERT(hasClient(), "can only append into a client buffer");
    updateElements(elements, count, _elementCount, defer);
}

void GLArrayBuffer::removeElements(ssize_t count, ssize_t begin, bool defer)
{
    const auto ec = getElementCount();
    CCASSERT(hasClient(),         "can only remove from a client buffer");
    CCASSERT(begin < ec,          "removeElements begin must be within range");
    CCASSERT(begin + count <= ec, "removeElements count must be within range");
    _elementCount -= count;
    const intptr_t src = (intptr_t)_elements + (begin + count) * getElementSize();
    updateElements((void*)src, _elementCount - begin, begin, defer);
}

void GLArrayBuffer::addCapacity(ssize_t count, bool zero)
{
    setCapacity(count + getCapacity(), zero);
}

void GLArrayBuffer::swapElements(ssize_t source, ssize_t dest, ssize_t count)
{
    const auto ec = getElementCount();
    CCASSERT(hasClient(),          "can only swap elements in a client buffer");
    CCASSERT(source < ec,          "swapElements source must be within range");
    CCASSERT(source + count <= ec, "swapElements source + count must be within range");
    CCASSERT(dest < ec,            "swapElements dest must be within range");
    CCASSERT(dest + count <= ec,   "swapElements dest + count must be within range");
    const ssize_t s1 = source;
    const ssize_t s2 = s1 + count;
    const ssize_t d1 = dest;
    const ssize_t d2 = d1 + count;
    const ssize_t overlap = s1 < d1 ? s2 - d1 : d2 - s1;
    const ssize_t count2 = overlap > 0 ? count - overlap : count;
    const auto es = getElementSize();
    const auto tmpptr = CC_ALLOCA(count2 * es);
    const auto srcptr = (void*)((intptr_t)_elements + s1 * es);
    const auto dstptr = (void*)((intptr_t)_elements + d1 * es);
    memcpy (tmpptr, dstptr, count2 * es);
    memmove(dstptr, srcptr, count );
    memmove(srcptr, tmpptr, count2);
}

void GLArrayBuffer::moveElements(ssize_t source, ssize_t dest, ssize_t count)
{
    const auto es = getElementSize();
    const auto srcptr = (void*)((intptr_t)_elements + source * es);
    updateElements(srcptr, count, dest);
}

void GLArrayBuffer::bindAndCommit(const void* elements, ssize_t count, ssize_t begin)
{
    CCASSERT(true == hasNative(), "GLArrayBuffer::bindAndCommit : array has no native buffer");

    if (_vbo)
        GL::bindVBO(_target, _vbo);

    if (false == isDirty())
        return;
    
    // default to all elements
    if (nullptr == elements)
        elements = _elements;
    
    // default to all elements
    if (0 == count)
        count = _elementCount;

    if (0 == _vbo)
    {
        glGenBuffers(1, &_vbo);
        _vboSize = getCapacityInBytes();
        CCASSERT(_vboSize, "_vboSize should not be 0");
        GL::bindVBO(_target, _vbo);
        glBufferData(_target, _vboSize, nullptr, _usage);
        glBufferData(_target, count * getElementSize(), elements, _usage);
        CHECK_GL_ERROR_DEBUG();
    }
    else
    {
        GL::bindVBO(_target, _vbo);
        const auto size = getCapacityInBytes();
        CCASSERT(size, "size should not be 0");
        if (size >= _vboSize)
        {
            _vboSize = size;
            glBufferData(_target, size, elements, _usage);
            CHECK_GL_ERROR_DEBUG();
       }
        else
        {
            intptr_t p = (intptr_t)elements + begin * _elementSize;
            glBufferSubData(_target, begin * _elementSize, count * _elementSize, (void*)p);
            CHECK_GL_ERROR_DEBUG();
        }
    }
    
    setDirty(false);
}

void GLArrayBuffer::clear()
{
    _elementCount = 0;
    _dirty = true;
}

void GLArrayBuffer::recreate() const
{
    if (glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        GL::bindVBO(_target, 0);
    }
    glGenBuffers(1, (GLuint*)&_vbo);
    GL::bindVBO(_target, _vbo);
    if (_elements)
    {
        glBufferData(_target, _elementSize * _elementCount, _elements, GL_STATIC_DRAW);
        GL::bindVBO(_target, _vbo);
        if(!glIsBuffer(_vbo))
        {
            CCLOGERROR("Renderer::recreate() : recreate VertexBuffer Error");
        }
    }
}

void GLArrayBuffer::setCapacity(ssize_t capacity, bool zero)
{
    if (capacity > _capacity)
    {
        if (hasClient())
        {
            auto capacityInBytes = capacity * _elementSize;
            _elements = realloc(_elements, capacityInBytes);
            
            if (zero)
            {
                intptr_t start = (intptr_t)_elements + _capacity * _elementSize;
                size_t count = _elementSize * (capacity - _capacity);
                memset((void*)start, 0, count);
            }
            _dirty = true;
        }
        _capacity = capacity;
    }
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
