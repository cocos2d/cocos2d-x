
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

#ifndef __CC_VERTEX_INDEX_BUFFER_H__
#define __CC_VERTEX_INDEX_BUFFER_H__

#include "base/CCRef.h"

NS_CC_BEGIN

class EventListenerCustom;

// @brief Generic renderer buffer for vertices or indices or anything that you can get
//        from the graphics API that is in array format.
//
//        Supports copying of the data to a client memory buffer which can be retrieved
//        or used to rebuild the graphics API buffer is cases where they are transient.
class RendererBuffer
    : public Ref
{
    RendererBuffer();

public:
    
    virtual ~RendererBuffer();
    
    int getElementSize() const;
    int getElementCount() const;
    
    bool updateElements(const void* elements, int count, int begin, bool copy = true);
    
    unsigned getSize() const
    {
        return getElementCount() * getElementSize();
    }
    
    CC_DEPRECATED_ATTRIBUTE uint32_t getVBO() const
    {
        return _vbo;
    }

    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }

protected:

    bool init(int elementSize, int elementCount, bool copy);
    void recreateVBO() const;

protected:
    
    EventListenerCustom* _recreateVBOEventListener;
    uint32_t _vbo;
    
    unsigned _elementSize;
    unsigned _elementCount;
    
    void* _elements;

    static bool _enableShadowCopy;
};


class CC_DLL VertexBuffer
    : public RendererBuffer
{
public:
    
    template <class T = VertexBuffer>
    static T* create(int size, int count, bool copy = false)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(size, count, copy))
        {
            result->autorelease();
            return result;
        }
        CC_SAFE_DELETE(result);
        return nullptr;
    }
    
    CC_DEPRECATED_ATTRIBUTE int getSizePerVertex() const { return getElementSize(); }
    CC_DEPRECATED_ATTRIBUTE int getVertexNumber() const { return getElementCount(); }
    CC_DEPRECATED_ATTRIBUTE bool updateVertices(const void* vertices, int count, int begin) { return updateElements(vertices, count, begin); }
};


class CC_DLL IndexBuffer : public RendererBuffer
{
    IndexBuffer();

public:
    
    enum class IndexType
    {
        INDEX_TYPE_SHORT_16,
        INDEX_TYPE_UINT_32
    };
    
    template <class T = IndexBuffer>
    static IndexBuffer* create(IndexType type, int count, bool copy = false)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(type, count, copy))
        {
            result->autorelease();
            return result;
        }
        CC_SAFE_DELETE(result);
        return nullptr;
    }
    
    IndexType getType() const
    {
        return _type;
    }
    
    CC_DEPRECATED_ATTRIBUTE int getSizePerIndex() const { return getElementSize(); }
    CC_DEPRECATED_ATTRIBUTE int getIndexNumber() const { return getElementCount(); }
    CC_DEPRECATED_ATTRIBUTE bool updateIndices(const void* indices, int count, int begin) { return updateElements(indices, count, begin); }

protected:
    
    bool init(IndexType type, int number, bool copy)
    {
        if (!RendererBuffer::init(IndexType::INDEX_TYPE_SHORT_16 == _type ? 2 : 4, number, copy))
            return false;
        _type = type;
        return true;
    }
    
protected:

    IndexType _type;
};


NS_CC_END

#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
