
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
#include "base/CCDirector.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
bool RendererBuffer::_enableShadowCopy = true;
#else
bool RendererBuffer::_enableShadowCopy = false;
#endif

RendererBuffer::RendererBuffer()
    : _recreateVBOEventListener(nullptr)
    , _vbo(0)
    , _elementSize(0)
    , _elementCount(0)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _recreateVBOEventListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RENDERER_RECREATED, [this](EventCustom* event){this->recreateVBO();};);
#endif
}

RendererBuffer::~RendererBuffer()
{
    // GAPI delete buffer
    if (glIsBuffer(_vbo))
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
    
    if (nullptr != _elements)
    {
        free(_elements);
        _elements = nullptr;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreateVBOEventListener);
#endif
}

bool RendererBuffer::init(int elementSize, int elementCount, bool copy)
{
    if(0 == elementSize || 0 == elementCount)
        return false;
    
    _elementSize  = elementSize;
    _elementCount = elementCount;
    
//    if (isShadowCopyEnabled())
//        ensureCopyCapacity(getSize());
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getSize(), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

int RendererBuffer::getElementCount() const
{
    return _elementCount;
}

int RendererBuffer::getElementSize() const
{
    return _elementSize;
}

bool RendererBuffer::updateElements(const void* elements, int count, int begin, bool copy)
{
    if (count <= 0 || nullptr == elements)
        return false;
    
    if (begin < 0)
    {
        CCLOGERROR("Update vertices with begin = %d, will set begin to 0", begin);
        begin = 0;
    }
    
    if (count + begin >= _elementCount)
    {
        CCLOGERROR("updated vertices exceed the max size of vertex buffer, will set count to _vertexNumber-begin");
        count = _elementCount - begin;
    }
    
    if ((copy || isShadowCopyEnabled()) && _elements)
    {
        intptr_t p = (intptr_t)_elements + begin * _elementSize;
        memcpy((void*)p, elements, count * _elementSize);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, begin * _elementSize, count * _elementSize, elements);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

void RendererBuffer::recreateVBO() const
{
    glGenBuffers(1, (GLuint*)&_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    if (_elements)
    {
        glBufferData(GL_ARRAY_BUFFER, _elementSize * _elementCount, _elements, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if(!glIsBuffer(_vbo))
        {
            CCLOGERROR("Renderer::recreateVBO() : recreate VertexBuffer Error");
        }
    }
}

NS_CC_END
