
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

#include "base/ccMacros.h"
#include "base/CCRef.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)
    #define SUPPORT_NO_CLIENT_SIDE_ARRAYS
#endif

NS_CC_BEGIN

class EventListenerCustom;
class VertexData;

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
        Invalid,
        Client  = (1<<0), // Maintains a Client memory buffer to store elements.
        Native  = (1<<2), // Maintains a Native buffer to store elements.
        Default = Native,
        All     = Client | Native
    };
    
    enum class ArrayMode
    {
        Invalid,
        Immutable, // GL_STATIC_DRAW
        LongLived, // GL_DYNAMIC_DRAW
        Dynamic    // GL_STREAMED_DRAW
    };
    
    virtual ~GLArrayBuffer();
    
    // @brief updates a region of the client and native buffer
    //        if defer is true, then the native buffer will not be updated.
    void updateElements(const void* elements, size_t count, size_t begin = 0, bool defer = true);
    
    // @brief inserts elements into the client and native buffer.
    //        if defer is true, then the native buffer will not be updated.
    void insertElements(const void* elements, size_t count, size_t begin, bool defer = true);

    // @brief appends elements into the client and native buffer.
    //        if defer is true, then the native buffer will not be updated.
    void appendElements(const void* elements, size_t count, bool defer = true);

    // @brief removes elements from the client and native buffer.
    //        if defer is true, then the native buffer is not updated.
    void removeElements(size_t count, size_t begin, bool defer = true);
    
    // @brief increases the capacity of the buffer by count elements
    //        optionally zeroes out the elements.
    void addCapacity(size_t count, bool zero = false);
    
    // @brief swaps elements in the buffer without resizing the buffer
    //        if defer is true, then the native buffer is not updated.
    void swapElements(size_t source, size_t dest, size_t count);

    // @brief moves elements in the buffer to the dest index.
    //        if defer is true, then the native buffer is not updated.
    void moveElements(size_t source, size_t dest, size_t count);

    // @brief if dirty, copies elements to the client buffer (if any)
    // and optionally submits the elements to the native buffer (if any)
    // if elements is null, then the entire client is commited to native. 
    void bindAndCommit(const void* elements = nullptr, size_t count = 0, size_t begin = 0);

    size_t getSize() const
    {
        return getElementCount() * getElementSize();
    }
    
    size_t getCapacityInBytes() const
    {
        return getCapacity() * getElementSize();
    }
    
    CC_DEPRECATED_ATTRIBUTE uint32_t getVBO() const
    {
        return _vbo;
    }

    void setElementCount(size_t count)
    {
        CCASSERT(count <= _capacity, "element count cannot exceed capacity");
        if (count != _elementCount)
        {
            _elementCount = count;
            setDirty(true);
        }
    }
    
    size_t getElementCount() const
    {
        return _elementCount;
    }
    
    size_t getElementSize() const
    {
        return _elementSize;
    }
    
    size_t getCapacity() const
    {
        return _capacity;
    }
    
    bool hasClient() const
    {
        return _arrayType & ArrayType::Client ? true : false;
    }
    
    bool hasNative() const
    {
        return _arrayType & ArrayType::Native ? true : false;
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

    void recreate() const;
    
    // @brief returns the client array if present, otherwise nullptr
    template <typename T = void>
    T* getElementsT() const
    {
        return hasClient() ? static_cast<T*>(_elements) : nullptr;
    }

    // @brief append
    template <typename T>
    size_t appendElementsT(T* source, size_t elements = 1, bool defer = true)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        appendElements((const void*)source, mult * elements, defer);
        return getSize();
    }
    
    template <typename T>
    void updateElementsT(const T* element, size_t count, size_t begin, bool defer = true)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        updateElements((const void*)element, mult * count, mult * begin, defer);
    }
    
    template <typename T>
    void insertElementsT(const T* element, size_t count, size_t begin, bool defer = true)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        insertElements((const void*)element, mult * count, mult * begin, defer);
    }
    
    template <typename T>
    void removeElementsT(size_t count, size_t begin, bool defer = true)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        removeElements(mult * count, mult * begin, defer);
    }
    
    template <typename T>
    void addCapacityT(size_t count, bool zero = false)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        addCapacity(mult * count, zero);
    }
    
    template <typename T>
    void swapElementsT(size_t source, size_t dest, size_t count)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        swapElements(mult * source, mult * dest, mult * count);
    }

    template <typename T>
    void moveElementsT(size_t source, size_t dest, size_t count)
    {
        CCASSERT(0 == sizeof(T) % getElementSize(), "elements must divide evenly into elementSize");
        auto mult = sizeof(T) / getElementSize();
        moveElements(mult * source, mult * dest, mult * count);
    }
    
protected:

    GLArrayBuffer();

    bool init(size_t elementSize, size_t maxElements, ArrayType arrayType, ArrayMode arrayMode, bool zero);
    void setCapacity(size_t capacity, bool zero);
    
    // @brief for OpenGL this provides the binding target of the array.
    virtual int nativeBindTarget() const = 0;

protected:

    // native only
    uint32_t _vbo;
    size_t _vboSize;
    int _target;
    
    // client buffer only
    size_t _elementCount;
    void* _elements;
    
    size_t _elementSize;
    size_t _capacity;

    ArrayType _arrayType;
    ArrayMode _arrayMode;
    
    unsigned _usage;
    bool _dirty;
};


class CC_DLL VertexBuffer
    : public GLArrayBuffer
{
public:
    
    template <class T = VertexBuffer>
    static T* create(size_t size, size_t count, ArrayType arrayType = ArrayType::Default, ArrayMode arrayMode = ArrayMode::LongLived, bool zero = false)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(size, count, arrayType, arrayMode, zero))
        {
            result->autorelease();
            return result;
        }
        CC_SAFE_DELETE(result);
        return nullptr;
    }
    
    CC_DEPRECATED_ATTRIBUTE int getSizePerVertex() const { return (int)getElementSize(); }
    CC_DEPRECATED_ATTRIBUTE int getVertexNumber() const { return (int)getElementCount(); }
    CC_DEPRECATED_ATTRIBUTE bool updateVertices(const void* vertices, int count, int begin) { updateElements(vertices, count, begin); return true; }

protected:
    
    int nativeBindTarget() const;
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
    static IndexBuffer* create(IndexType type, size_t count, ArrayType arrayType = ArrayType::Default, ArrayMode arrayMode = ArrayMode::LongLived, bool zero = false)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(type, count, arrayType, arrayMode, zero))
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
    
    CC_DEPRECATED_ATTRIBUTE int getSizePerIndex() const { return (int)getElementSize(); }
    CC_DEPRECATED_ATTRIBUTE int getIndexNumber() const { return (int)getElementCount(); }
    CC_DEPRECATED_ATTRIBUTE bool updateIndices(const void* indices, int count, int begin) { updateElements(indices, count, begin); return true; }

protected:
    
    IndexBuffer()
        : _type(IndexType::INDEX_TYPE_NONE)
    {}

    bool init(IndexType type, size_t count, ArrayType arrayType, ArrayMode arrayMode, bool zero)
    {
        if (!GLArrayBuffer::init(IndexType::INDEX_TYPE_SHORT_16 == type ? 2 : 4, count, arrayType, arrayMode, zero))
            return false;
        _type = type;
        return true;
    }

    // @brief for OpenGL this provides the binding target of the array.
    int nativeBindTarget() const;
    
protected:

    IndexType _type;
};


NS_CC_END

#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
