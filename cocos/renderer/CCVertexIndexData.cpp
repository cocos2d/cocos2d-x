/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

VertexData* VertexData::create()
{
    VertexData* result = new (std::nothrow) VertexData();
    if(result)
    {
        result->autorelease();
        return result;
    }

    CC_SAFE_DELETE(result);
    return nullptr;
}

size_t VertexData::getVertexStreamCount() const
{
    return _vertexStreams.size();
}

bool VertexData::setStream(VertexBuffer* buffer, const VertexStreamAttribute& stream)
{
    if( buffer == nullptr ) return false;
    auto iter = _vertexStreams.find(stream._semantic);
    if(iter == _vertexStreams.end())
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

VertexBuffer* VertexData::getStreamBuffer(int semantic) const
{
    auto iter = _vertexStreams.find(semantic);
    if(iter == _vertexStreams.end()) return nullptr;
    else return iter->second._buffer;
}

VertexData::VertexData()
{
    
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
    for(auto& element : _vertexStreams)
    {
        flags = flags | (1 << element.second._stream._semantic);
    }
    
    GL::enableVertexAttribs(flags);

    int lastVBO = -1;
    for(auto& element : _vertexStreams)
    {
        //glEnableVertexAttribArray((GLint)element.second._stream._semantic);
        auto vertexStreamAttrib = element.second._stream;
        auto vertexBuffer = element.second._buffer;

        // don't call glBindBuffer() if not needed. Expensive operation.
        int vbo = vertexBuffer->getVBO();
        if (vbo != lastVBO) {
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getVBO());
            lastVBO = vbo;
        }
        glVertexAttribPointer(GLint(vertexStreamAttrib._semantic),
                              vertexStreamAttrib._size,
                              vertexStreamAttrib._type,
                              vertexStreamAttrib._normalize,
                              vertexBuffer->getSizePerVertex(),
                              (GLvoid*)((long)vertexStreamAttrib._offset));
    }
}

NS_CC_END
