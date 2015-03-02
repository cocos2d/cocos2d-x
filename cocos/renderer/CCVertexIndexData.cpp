/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "renderer/CCVertexIndexData.h"
#include "platform/CCGL.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCConfiguration.h"

// TODO
// - use buffers instead of streams for clearing to avoid duplication

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#define SUPPORT_EVENT_RENDERER_RECREATED
#endif

NS_CC_BEGIN

VertexData::VertexData(Primitive primitive)
    : _indices(nullptr)
    , _interleaved(false)
    , _dirty(true)
    , _vao(0)
    , _drawingPrimitive(primitive)
{
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    _recreateEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, [this](EventCustom* event){this->recreate();});
#endif
}

VertexData::~VertexData()
{
    for (auto& element : _vertexStreams)
        element.second._buffer->release();
    _vertexStreams.clear();
    CC_SAFE_RELEASE(_indices);
    
    if (glIsBuffer(_vao))
    {
        glDeleteVertexArrays(1, (GLuint*)&_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
    
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateEventListener);
#endif
}

bool VertexData::addStream(GLArrayBuffer* buffer, const VertexAttribute& stream)
{
    if (nullptr == buffer)
        return false;
    
    setDirty(true);
    
    auto iter = _vertexStreams.find(stream._semantic);
    if (iter == _vertexStreams.end())
    {
        buffer->retain();
        auto& bufferAttribute = _vertexStreams[stream._semantic];
        bufferAttribute._buffer = buffer;
        bufferAttribute._stream = stream;
    }
    else
    {
        buffer->retain();
        iter->second._buffer->release();
        iter->second._stream = stream;
        iter->second._buffer = buffer;
    }
    
    _buffers.insert(tBuffers::value_type(buffer));
    
    // flag whether or not this vertex data is interleaved or not.
    _interleaved = determineInterleave();
    
    return true;
}

void VertexData::removeStream(int semantic)
{
    auto iter = _vertexStreams.find(semantic);
    if (iter != _vertexStreams.end())
    {
        auto buffer = iter->second._buffer;
        auto bi = _buffers.find(buffer);
        if (bi != _buffers.end())
            _buffers.erase(bi);
        
        iter->second._buffer->release();
        _vertexStreams.erase(iter);
    }

    _interleaved = determineInterleave();

    setDirty(true);
}

// @brief specify indexed drawing for vertex data with optional precision
void VertexData::setIndexBuffer(IndexBuffer* indices)
{
    CC_SAFE_RELEASE(_indices);
    _indices = indices;
    CC_SAFE_RETAIN(_indices);
}

void VertexData::removeIndexBuffer()
{
    CC_SAFE_RELEASE(_indices);
    _indices = nullptr;
}

const VertexAttribute* VertexData::getStreamAttribute(int semantic) const
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return &iter->second._stream;
}

VertexAttribute* VertexData::getStreamAttribute(int semantic)
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return &iter->second._stream;
}

ssize_t VertexData::draw(ssize_t start, ssize_t count)
{
    CCASSERT(start >= 0, "Invalid start value");
    CCASSERT(count >= 0, "Invalid count value");
    
    if (0 == count)
    {
        // if we are drawing indexed, then use the count of indices to draw
        count = _indices ? _indices->getElementCount() : this->getCount();
    }
    
    if (_vao)
    {
        GL::bindVAO(_vao);
        CHECK_GL_ERROR_DEBUG();
    }
    
    if (0 == _vao || isDirty())
    {
        if (0 == _vao && Configuration::getInstance()->supportsShareableVAO())
        {
            glGenVertexArrays(1, (GLuint*)&_vao);
            GL::bindVAO(_vao);
        }

        CHECK_GL_ERROR_DEBUG();
        
        for (auto& element : _vertexStreams)
        {
            auto vb = element.second._buffer;
            
            // commit any outstanding client side geometry to the native buffers.
            // for interleaved data this will happen only the first time through.
            vb->bindAndCommit();
            
            auto& attrib  = element.second;
            auto& stream  = attrib._stream;
            
            auto offset = stream._offset;
            auto stride = vb->getElementSize();
            
            glEnableVertexAttribArray(GLint(stream._semantic));
            glVertexAttribPointer(GLint(stream._semantic), stream._size, DataTypeToGL(stream._type), stream._normalize, (GLsizei)stride, (GLvoid*)(size_t)offset);
            
            CHECK_GL_ERROR_DEBUG();
        }

        if (_indices != nullptr)
            _indices->bindAndCommit();

        setDirty(false);
    }
    
    if (_indices != nullptr)
    {
        intptr_t offset = start * _indices->getElementSize();
        GLenum type = (_indices->getType() == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        glDrawElements((GLenum)_drawingPrimitive, (GLsizei)count, type, (GLvoid*)offset);
    }
    else
    {
        glDrawArrays((GLenum)_drawingPrimitive, (GLsizei)start, (GLsizei)count);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (_vao)
        GL::bindVAO(0);
    GL::bindVBO(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return count;
}

bool VertexData::empty() const
{
    for (auto b : _buffers)
    {
        if (0 != b->getElementCount())
            return false;
    }
    return true;
}

void VertexData::clear()
{
    _dirty = true;
    for (auto& b : _buffers)
        b->clear();
}

bool VertexData::isDirty() const
{
    if (_dirty)
        return true;
    for (auto b : _buffers)
        if (b->isDirty())
            return true;
    return false;
}

void VertexData::setDirty(bool dirty)
{
    _dirty = dirty;
    for (auto b : _buffers)
        b->setDirty(dirty);
}

ssize_t VertexData::getCount() const
{
    ssize_t count = 0;
    for (auto b : _buffers)
    {
        auto c = b->getElementCount();
        CCASSERT(0 == count || c == count, "all buffers must have the same vertex count");
        count = c;
    }
    return count;
}

ssize_t VertexData::getCapacity() const
{
    ssize_t capacity = 0;
    for (auto b : _buffers)
    {
        auto c = b->getCapacity();
        CCASSERT(0 == capacity || c == capacity, "all buffers must have the same capacity");
        capacity = c;
    }
    return capacity;
}

// @brief If all streams use the same buffer, then the data is interleaved.
bool VertexData::determineInterleave() const
{
    return _buffers.size() == 1;
}

void VertexData::append(GLArrayBuffer* buffer, void* source, ssize_t count)
{
    _dirty = true;
    buffer->appendElements(source, count);
}
    
void VertexData::recreate() const
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        if (glIsBuffer(_vao))
            glDeleteVertexArrays(1, (GLuint*)&_vao);
        glGenVertexArrays(1, (GLuint*)&_vao);
    }

    for (auto b : _buffers)
        b->recreate();
}

int VertexData::DataTypeToGL(DataType type)
{
    const static int gltypes[] = {GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT/*, GL_FIXED*/};
    unsigned t = (int)type;
    CCASSERT(t < sizeof(gltypes) / sizeof(gltypes[0]), "Invalid GL DataType index");
    return gltypes[t];
}

NS_CC_END
