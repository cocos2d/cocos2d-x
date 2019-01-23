/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"

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

VertexBuffer* VertexBuffer::create(int sizePerVertex, int vertexNumber, GLenum usage/* = GL_STATIC_DRAW*/)
{
    auto result = new (std::nothrow) VertexBuffer();
    if(result && result->init(sizePerVertex, vertexNumber, usage))
    {
        result->autorelease();
        return result;
    }
    CC_SAFE_DELETE(result);
    return nullptr;
    
}

VertexBuffer::VertexBuffer()
{
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto callBack = [this](EventCustom* event)
    {
        this->recreateVBO();
    };

    _recreateVBOEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, callBack);

#endif
}

VertexBuffer::~VertexBuffer()
{
    if (_vbo)
        _vbo->release();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool VertexBuffer::init(int sizePerVertex, int vertexNumber, GLenum usage/* = GL_STATIC_DRAW*/)
{
    if (0 == sizePerVertex || 0 == vertexNumber)
        return false;

    _sizePerVertex = sizePerVertex;
    _vertexNumber = vertexNumber;
    _usage = usage;
    
    if(isShadowCopyEnabled())
    {
        _shadowCopy.resize(sizePerVertex * _vertexNumber);
    }

    _vbo = backend::Device::getInstance()->newBuffer(sizePerVertex * _vertexNumber, backend::BufferType::VERTEX, backend::BufferUsage::STATIC);
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
    if (count <= 0 || nullptr == verts) return false;
    
    if (begin < 0)
    {
        CCLOGERROR("Update vertices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if (count + begin > _vertexNumber)
    {
        CCLOGERROR("updated vertices exceed the max size of vertex buffer, will set count to _vertexNumber-begin");
        count = _vertexNumber - begin;
    }
    
    if (isShadowCopyEnabled())
    {
        memcpy(&_shadowCopy[begin * _sizePerVertex], verts, count * _sizePerVertex);
    }

    //TODO minggo: updateSubData should use `const void*`.
    _vbo->updateSubData((void*)verts, begin * _sizePerVertex, count * _sizePerVertex);

    return true;
}

backend::Buffer* VertexBuffer::getVBO() const
{
    return _vbo;
}

void VertexBuffer::recreateVBO() const
{
//    CCLOG("come to foreground of VertexBuffer");
//    glGenBuffers(1, &_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//    const void* buffer = nullptr;
//    if (isShadowCopyEnabled())
//    {
//        buffer = &_shadowCopy[0];
//    }
//    CCLOG("recreate IndexBuffer with size %d %d", getSizePerVertex(), _vertexNumber);
//    glBufferData(GL_ARRAY_BUFFER, _sizePerVertex * _vertexNumber, buffer, _usage);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    if(!glIsBuffer(_vbo))
//    {
//        CCLOGERROR("recreate VertexBuffer Error");
//    }
}

int VertexBuffer::getSize() const
{
    return _sizePerVertex * _vertexNumber;
}

IndexBuffer* IndexBuffer::create(IndexType type, int number, GLenum usage/* = GL_STATIC_DRAW*/)
{
    auto result = new (std::nothrow) IndexBuffer();
    if(result && result->init(type, number, usage))
    {
        result->autorelease();
        return result;
    }
    CC_SAFE_DELETE(result);
    return nullptr;
}

IndexBuffer::IndexBuffer()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto callBack = [this](EventCustom* event)
    {
        this->recreateVBO();
    };

    _recreateVBOEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, callBack);
#endif
}

IndexBuffer::~IndexBuffer()
{
    if (_vbo)
        _vbo->release();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool IndexBuffer::init(IndexBuffer::IndexType type, int number, GLenum usage/* = GL_STATIC_DRAW*/)
{
    if(number <=0 ) return false;
    
    _type = type;
    _indexNumber = number;
    _usage = usage;
    _vbo = backend::Device::getInstance()->newBuffer(getSize(), backend::BufferType::INDEX, backend::BufferUsage::STATIC);

    if (isShadowCopyEnabled())
        _shadowCopy.resize(getSize());

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
    if (count <= 0 || nullptr == indices) return false;
    
    if (begin < 0)
    {
        CCLOGERROR("Update indices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if(count + begin > _indexNumber)
    {
        CCLOGERROR("updated indices exceed the max size of vertex buffer, will set count to _indexNumber-begin");
        count = _indexNumber - begin;
    }
    
    _vbo->updateSubData((void*)indices, begin * getSizePerIndex(), count * getSizePerIndex());

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

backend::Buffer* IndexBuffer::getVBO() const
{
    return _vbo;
}

void IndexBuffer::recreateVBO() const
{
//    CCLOG("come to foreground of IndexBuffer");
//    glGenBuffers(1, &_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//    const void* buffer = nullptr;
//    if(isShadowCopyEnabled())
//    {
//        buffer = &_shadowCopy[0];
//    }
//    CCLOG("recreate IndexBuffer with size %d %d ", getSizePerIndex(), _indexNumber);
//    glBufferData(GL_ARRAY_BUFFER, getSize(), buffer, _usage);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    if(!glIsBuffer(_vbo))
//    {
//        CCLOGERROR("recreate IndexBuffer Error");
//    }
}

NS_CC_END
