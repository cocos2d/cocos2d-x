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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#define SUPPORT_EVENT_RENDERER_RECREATED
#endif

NS_CC_BEGIN

VertexData::VertexData(Primitive primitive)
    : _interleaved(false)
    , _dirty(false)
    , _count(0)
    , _vao(0)
    , _indices(nullptr)
    , _drawingPrimitive(primitive)
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, (GLuint*)&_vao);
    }
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    _recreateEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, [this](EventCustom* event){this->recreate();};);
#endif
}

VertexData::~VertexData()
{
    for (auto& element : _vertexStreams)
        element.second._buffer->release();
    _vertexStreams.clear();
    
    if (glIsBuffer(_vao))
    {
        glDeleteVertexArrays(1, (GLuint*)&_vao);
        _vao = 0;
    }
    
#ifdef SUPPORT_EVENT_RENDERER_RECREATED
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateEventListener);
#endif
}

bool VertexData::addStream(GLArrayBuffer* buffer, const VertexStreamAttribute& stream)
{
    if (nullptr == buffer)
        return false;
    
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
}

const VertexStreamAttribute* VertexData::getStreamAttribute(int semantic) const
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return &iter->second._stream;
}

VertexStreamAttribute* VertexData::getStreamAttribute(int semantic)
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return &iter->second._stream;
}

void VertexData::draw(unsigned start, unsigned count)
{
    if (0 == count)
        count = _count;
    
    if (_vao)
    {
        GL::bindVAO(_vao);
        CHECK_GL_ERROR_DEBUG();
    }
    
    if (0 == _vao || isDirty())
    {
        CHECK_GL_ERROR_DEBUG();
        
        for (auto& element : _vertexStreams)
        {
            auto vb = element.second._buffer;
            
            // commit any outstanding client side geometry to the native buffers.
            // for interleaved data this will happen only the first time through.
            vb->commit();
            
            // this is redundant for interleaved streams, but needed for non-interleaved to work.
            // the call is trivially rejected by the GL state cache.
            GL::bindVBO(GL_ARRAY_BUFFER, vb->getVBO());
            
            auto& attrib  = element.second;
            auto& stream  = attrib._stream;
            auto offset = attrib._stream._offset;
            auto stride = vb->getElementSize();
            glEnableVertexAttribArray(GLint(stream._semantic));
            glVertexAttribPointer(GLint(stream._semantic), stream._size, stream._type, stream._normalize, (GLsizei)stride, (GLvoid*)(size_t)offset);
            CHECK_GL_ERROR_DEBUG();
        }

        setDirty(false);
    }
    
    if (_indices != nullptr)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indices->getVBO());
        intptr_t offset = start * _indices->getElementSize();
        GLenum type = (_indices->getType() == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        glDrawElements((GLenum)_drawingPrimitive, count, type, (GLvoid*)offset);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        glDrawArrays((GLenum)_drawingPrimitive, start, count);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (_vao)
        GL::bindVAO(0);
    GL::bindVBO(GL_ARRAY_BUFFER, 0);
}

bool VertexData::empty() const
{
    for (auto& e : _vertexStreams)
    {
        auto& bufferAttribute = e.second;
        if (0 != bufferAttribute._buffer->getElementCount())
            return false;
    }
    return true;
}

void VertexData::clear()
{
    _count = 0;
    _dirty = false;
    for (auto& e : _vertexStreams)
    {
        auto& bufferAttribute = e.second;
        bufferAttribute._buffer->clear();
    }
}

bool VertexData::isDirty() const
{
    if (_dirty)
        return true;
    for (auto& e : _vertexStreams)
    {
        auto& bufferAttribute = e.second;
        if (bufferAttribute._buffer->isDirty())
            return true;
    }
    return false;
}

void VertexData::setDirty(bool dirty)
{
    _dirty = dirty;
    for (auto& e : _vertexStreams)
    {
        auto& bufferAttribute = e.second;
        bufferAttribute._buffer->setDirty(dirty);
    }
}

size_t VertexData::count() const
{
    return _count;
}

// @brief If all streams use the same buffer, then the data is interleaved.
bool VertexData::determineInterleave() const
{
    return _buffers.size() == 1;
}

void VertexData::append(GLArrayBuffer* buffer, void* source, unsigned size, unsigned count)
{
    _dirty = true;
    buffer->append(source, size, count);
}
    
void VertexData::recreate() const
{
    for (auto b : _buffers)
        b->recreate();
}

NS_CC_END
