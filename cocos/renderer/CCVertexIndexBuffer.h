
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)
    #define SUPPORT_NO_CLIENT_SIDE_ARRAYS
#endif

NS_CC_BEGIN

class EventListenerCustom;

// @brief OpenGL buffer for vertices or indices or anything that you can get
//        from the GL API that is in array format.
//        - copying of the data to a client memory buffer which can be retrieved
//          or used to rebuild the GL buffer is cases where they are transient.
//        - optional use of vao with vbo if supported.
//        - handles cases where client buffers are not supported, i.e. Emscripten.
//        - copies to GL buffer from client memory on demand.
//        - can transform into another GLArrayBuffer on demand.
//        - knows how to draw itself.
class CC_DLL GLArrayBuffer
    : public Ref
{
public:
    
    enum ArrayType
    {
        Client  = (1<<0), // Maintains a Client memory buffer to store elements.
        Native  = (1<<2), // Maintains a Native buffer to store elements.
        Default = Native,
        All     = Client | Native
    };
    
    enum class ArrayMode
    {
        Immutable, // GL_STATIC_DRAW
        LongLived, // GL_DYNAMIC_DRAW
        Dynamic    // GL_STREAMED_DRAW
    };
    
    virtual ~GLArrayBuffer();
    
    // @brief updates a region of the client and native buffer
    //        if defer is true, then the native buffer will not be updated.
    bool updateElements(const void* elements, int count, int begin = 0, bool defer = true);
    
    // @brief if dirty, submits the client buffer to the native buffer
    bool update(int count = 0, int begin = 0);
    
    size_t getSize() const
    {
        return getElementCount() * getElementSize();
    }
    
    CC_DEPRECATED_ATTRIBUTE uint32_t getVBO() const
    {
        return _vbo;
    }

    int getElementCount() const
    {
        return _elementCount;
    }
    
    int getElementSize() const
    {
        return _elementSize;
    }
    
    bool hasClient() const
    {
        return _arrayType & ArrayType::Client;
    }
    
    bool hasNative() const
    {
        return _arrayType & ArrayType::Native;
    }
    
    bool isDirty() const
    {
        return _dirty;
    }
    
    void setDirty(bool dirty)
    {
        _dirty = dirty;
    }
    
    void clear();

    // @brief append
    size_t append(void* source, size_t size, size_t elements = 1);

protected:

    GLArrayBuffer();

    bool init(int elementSize, int elementCount, ArrayType arrayType, ArrayMode arrayMode);
    void ensureCapacity(size_t capacity);

    void recreate() const;
    
protected:

    uint32_t _vbo;
    
    unsigned _elementSize;
    unsigned _elementCount;
    
    void* _elements;
    ArrayType _arrayType;
    ArrayMode _arrayMode;
    
    int _opaqueDrawMode;
    bool _dirty;
};


class CC_DLL VertexBuffer
    : public GLArrayBuffer
{
public:
    
    template <class T = VertexBuffer>
    static T* create(int size, int count, ArrayType arrayType = ArrayType::Default, ArrayMode arrayMode = ArrayMode::LongLived)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(size, count, arrayType, arrayMode))
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


class CC_DLL IndexBuffer
    : public GLArrayBuffer
{
public:
    
    enum class IndexType
    {
        INDEX_TYPE_NONE = -1,
        INDEX_TYPE_SHORT_16,
        INDEX_TYPE_UINT_32
    };
    
    template <class T = IndexBuffer>
    static IndexBuffer* create(IndexType type, int count, ArrayType arrayType = ArrayType::Default, ArrayMode arrayMode = ArrayMode::LongLived)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(type, count, arrayType, arrayMode))
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
    
    IndexBuffer()
        : _type(IndexType::INDEX_TYPE_NONE)
    {}

    bool init(IndexType type, int number, ArrayType arrayType, ArrayMode arrayMode)
    {
        if (!GLArrayBuffer::init(IndexType::INDEX_TYPE_SHORT_16 == _type ? 2 : 4, number, arrayType, arrayMode))
            return false;
        _type = type;
        return true;
    }
    
protected:

    IndexType _type;
};


NS_CC_END

#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
