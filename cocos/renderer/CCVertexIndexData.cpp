/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

GLint VertexData::getGLSize(VertexType type)
{
    if(VertexType::FLOAT1 == type)
    {
        return 1;
    }
    else if(VertexType::FLOAT2 == type)
    {
        return 2;
    }
    else if(VertexType::FLOAT3 == type)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

GLenum VertexData::getGLType(VertexType type)
{
    if(VertexType::BYTE4 == type)
    {
        return GL_UNSIGNED_BYTE;
    }
    else
    {
        return GL_FLOAT;
    }
}

GLint VertexData::getGLSemanticBinding(VertexSemantic semantic)
{
    return GLint(semantic);
}

void VertexData::use()
{
    for(auto& element : _vertexStreams)
    {
        glEnableVertexAttribArray((GLint)element.second._stream._semantic);
        glBindBuffer(GL_ARRAY_BUFFER, element.second._buffer->getVBO());
        glVertexAttribPointer(GLint(element.second._stream._semantic),element.second._stream._size,
                              element.second._stream._type,element.second._stream._normalize, element.second._buffer->getSizePerVertex(), (GLvoid*)element.second._stream._offset);
    }
}

IndexData* IndexData::create(IndexBuffer* buffer, int start, int count)
{
    IndexData* result = new (std::nothrow) IndexData();
    if(result && result->init(buffer, start, count))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

IndexData::IndexData()
: _buffer(nullptr)
, _start(0)
, _count(0)
{
}

IndexData::~IndexData()
{
    CC_SAFE_RELEASE_NULL(_buffer);
}

bool IndexData::init(IndexBuffer* buffer, int start, int count)
{
    if(count == 0) return false;
    if(_buffer != buffer)
    {
        CC_SAFE_RELEASE_NULL(_buffer);
        CC_SAFE_RETAIN(buffer);
        _buffer = buffer;
    }
    
    _start = start;
    _count = count;
    
    return false;
}

NS_CC_END
