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

#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
bool VertexBuffer::_enableShadowCopy = true;
#else
bool VertexBuffer::_enableShadowCopy = false;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
bool IndexBuffer::_enableShadowCopy = true;
#else
bool IndexBuffer::_enableShadowCopy = false;
#endif

VertexBuffer* VertexBuffer::create(int sizePerVertex, int vertexNumber)
{
    auto result = new (std::nothrow) VertexBuffer();
    if(result && result->init(sizePerVertex, vertexNumber))
    {
        result->autorelease();
        return result;
    }
    CC_SAFE_DELETE(result);
    return nullptr;
    
}

VertexBuffer::VertexBuffer()
: _recreateVBOEventListener(nullptr)
, _vbo(0)
, _sizePerVertex(0)
, _vertexNumber(0)
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto callBack = [this](EventCustom* event)
    {
        this->recreateVBO();
    };

    _recreateVBOEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, callBack);

#endif
}

VertexBuffer::~VertexBuffer()
{
    if(glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool VertexBuffer::init(int sizePerVertex, int vertexNumber)
{
    if(0 == sizePerVertex || 0 == vertexNumber)
        return false;
    _sizePerVertex = sizePerVertex;
    _vertexNumber = vertexNumber;
    
    if(isShadowCopyEnabled())
    {
        _shadowCopy.resize(sizePerVertex * _vertexNumber);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getSize(), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

int VertexBuffer::getSizePerVertex() const
{
    return _sizePerVertex;
}

int VertexBuffer::getVertexNumber() const
{
    return _vertexNumber;
}

bool VertexBuffer::updateVertices(const void* verts, int count, int begin)
{
    if(count <= 0 || nullptr == verts) return false;
    
    if(begin < 0)
    {
        CCLOGERROR("Update vertices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if(count + begin > _vertexNumber)
    {
        CCLOGERROR("updated vertices exceed the max size of vertex buffer, will set count to _vertexNumber-begin");
        count = _vertexNumber - begin;
    }
    
    if(isShadowCopyEnabled())
    {
        memcpy(&_shadowCopy[begin * _sizePerVertex], verts, count * _sizePerVertex);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, begin * _sizePerVertex, count * _sizePerVertex, verts);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

GLuint VertexBuffer::getVBO() const
{
    return _vbo;
}

void VertexBuffer::recreateVBO() const
{
    CCLOG("come to foreground of VertexBuffer");
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    const void* buffer = nullptr;
    if(isShadowCopyEnabled())
    {
        buffer = &_shadowCopy[0];
    }
    CCLOG("recreate IndexBuffer with size %d %d", getSizePerVertex(), _vertexNumber);
    glBufferData(GL_ARRAY_BUFFER, _sizePerVertex * _vertexNumber, buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(!glIsBuffer(_vbo))
    {
        CCLOGERROR("recreate VertexBuffer Error");
    }
}

int VertexBuffer::getSize() const
{
    return _sizePerVertex * _vertexNumber;
}

IndexBuffer* IndexBuffer::create(IndexType type, int number)
{
    auto result = new (std::nothrow) IndexBuffer();
    if(result && result->init(type, number))
    {
        result->autorelease();
        return result;
    }
    CC_SAFE_DELETE(result);
    return nullptr;
}

IndexBuffer::IndexBuffer()
: _vbo(0)
, _type(IndexType::INDEX_TYPE_SHORT_16)
, _indexNumber(0)
, _recreateVBOEventListener(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto callBack = [this](EventCustom* event)
    {
        this->recreateVBO();
    };

    _recreateVBOEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, callBack);
#endif
}

IndexBuffer::~IndexBuffer()
{
    if(glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool IndexBuffer::init(IndexBuffer::IndexType type, int number)
{
    if(number <=0 ) return false;
    
    _type = type;
    _indexNumber = number;
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getSize(), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    if(isShadowCopyEnabled())
    {
        _shadowCopy.resize(getSize());
    }
    
    return true;
}

IndexBuffer::IndexType IndexBuffer::getType() const
{
    return _type;
}

int IndexBuffer::getSizePerIndex() const
{
    return IndexType::INDEX_TYPE_SHORT_16 == _type ? 2 : 4;
}

int IndexBuffer::getIndexNumber() const
{
    return _indexNumber;
}

bool IndexBuffer::updateIndices(const void* indices, int count, int begin)
{
    if(count <= 0 || nullptr == indices) return false;
    
    if(begin < 0)
    {
        CCLOGERROR("Update indices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if(count + begin > _indexNumber)
    {
        CCLOGERROR("updated indices exceed the max size of vertex buffer, will set count to _indexNumber-begin");
        count = _indexNumber - begin;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, begin * getSizePerIndex(), count * getSizePerIndex(), indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    if(isShadowCopyEnabled())
    {
        memcpy(&_shadowCopy[begin * getSizePerIndex()], indices, count * getSizePerIndex());
    }
    
    return true;
}

int IndexBuffer::getSize() const
{
    return getSizePerIndex() * _indexNumber;
}

GLuint IndexBuffer::getVBO() const
{
    return _vbo;
}

void IndexBuffer::recreateVBO() const
{
    CCLOG("come to foreground of IndexBuffer");
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    const void* buffer = nullptr;
    if(isShadowCopyEnabled())
    {
        buffer = &_shadowCopy[0];
    }
    CCLOG("recreate IndexBuffer with size %d %d ", getSizePerIndex(), _indexNumber);
    glBufferData(GL_ARRAY_BUFFER, getSize(), buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(!glIsBuffer(_vbo))
    {
        CCLOGERROR("recreate IndexBuffer Error");
    }
}

NS_CC_END
