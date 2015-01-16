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
#include "renderer/ccGLStateCache.h"
#include "renderer/CCVertexIndexBuffer.h"

NS_CC_BEGIN

VertexData::VertexData()
    : _interleaved(false)
    , _dirty(false)
{}

bool VertexData::setStream(GLArrayBuffer* buffer, const VertexStreamAttribute& stream)
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
    
    _interleaved = determineInterleave();
    
    return true;
}

void VertexData::removeStream(int semantic)
{
    auto iter = _vertexStreams.find(semantic);
    if(iter != _vertexStreams.end())
    {
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

GLArrayBuffer* VertexData::getStreamBuffer(int semantic) const
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return iter->second._buffer;
}

VertexData::~VertexData()
{
    for(auto& element : _vertexStreams)
    {
        element.second._buffer->release();
    }
    _vertexStreams.clear();
}

void VertexData::use()
{
    uint32_t flags(0);
    for (auto& element : _vertexStreams)
    {
        flags = flags | (1 << element.second._stream._semantic);
    }
    
    GL::enableVertexAttribs(flags);
    
    for (auto& element : _vertexStreams)
    {
        auto& attrib = element.second;
        auto& stream = attrib._stream;
        
        glBindBuffer(GL_ARRAY_BUFFER, attrib._buffer->getVBO());
        size_t offet = attrib._stream._offset;
        glVertexAttribPointer(GLint(stream._semantic), stream._size, stream._type, stream._normalize, attrib._buffer->getElementSize(), (GLvoid*)offet);
    }
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

// @brief If all streams use the same buffer, then the data is interleaved.
bool VertexData::determineInterleave() const
{
    size_t count = _vertexStreams.size();
    if (0 == count)
        return false;
    void* p = nullptr;
    for (auto& e : _vertexStreams)
    {
        if (nullptr == p)
        {
            p = e.second._buffer;
            continue;
        }
        else
        {
            if (p != e.second._buffer)
                return false;
        }
    }
    return true;
}

void VertexData::append(GLArrayBuffer* buffer, void* source, size_t size, size_t count)
{
    _dirty = true;
    buffer->append(source, size, count);
}

NS_CC_END
