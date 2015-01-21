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

#ifndef __CC_VERTEX_INDEX_DATA_H__
#define __CC_VERTEX_INDEX_DATA_H__

#include "base/CCRef.h"
#include <map>

NS_CC_BEGIN

class GLArrayBuffer;
class IndexBuffer;
class EventListenerCustom;

struct CC_DLL VertexStreamAttribute
{
    VertexStreamAttribute()
        : _normalize(false), _offset(0), _semantic(0), _type(0), _size(0)
    {}

    VertexStreamAttribute(int offset, int semantic, int type, int size)
        : _normalize(false), _offset(offset), _semantic(semantic), _type(type), _size(size)
    {}
    
    VertexStreamAttribute(int offset, int semantic, int type, int size, bool normalize)
        : _normalize(normalize), _offset(offset), _semantic(semantic), _type(type), _size(size)
    {}
    
    bool _indexed;
    bool _normalize;
    int _offset;
    int _semantic;
    int _type;
    int _size;
};

class CC_DLL VertexData
    : public Ref
{
public:
    
    enum Primitive
    {
        Points,
        Lines,
        LineLoop,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan
    };
    
    template <typename T = VertexData>
    static T* create(Primitive primitive)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(primitive))
        {
            result->autorelease();
            return result;
        }
        return nullptr;
    }

    virtual ~VertexData();
    
    bool init(Primitive primitive);

    // @brief Return the number of vertex streams
    size_t getVertexStreamCount() const;
    
    // @brief add vertex stream descriptors to a buffer 
    CC_DEPRECATED_ATTRIBUTE bool setStream(GLArrayBuffer* buffer, const VertexStreamAttribute& stream) { return addStream(buffer, stream); }
    bool addStream(GLArrayBuffer* vertices, const VertexStreamAttribute& stream);
    void removeStream(int semantic);

    const VertexStreamAttribute* getStreamAttribute(int semantic) const;
    VertexStreamAttribute* getStreamAttribute(int semantic);
        
    // @brief update and draw the buffer.
    void draw();
    
    // @brief true/false if all vertex buffers are empty
    bool empty() const;
    
    // @brief clears the vertex buffers associated with this vertex data
    void clear();
    
    // @brief returns the dirty status of the data or vertex streams
    bool isDirty() const;
    
    // @brief sets the dirty state of all vertex data
    void setDirty(bool dirty);
    
    // @brief returns the count of vertices added
    size_t count() const;
    
    template <typename T>
    void append(const T& vertex)
    {
        if (_interleaved)
        {
            for (auto& e : _vertexStreams)
            {
                auto const verts = e.second._buffer;
                append(verts, (void*)&vertex, sizeof(vertex));
                return;
            }
        }
        else
        {
            for (auto& e : _vertexStreams)
            {
                auto const verts = e.second._buffer;
                intptr_t p = (intptr_t)&vertex + e.second._stream._offset;
                append(verts, (void*)p, e.second._stream._size);
            }
        }
    }

protected:

    VertexData(Primitive primitive);

    void recreate() const;
    bool determineInterleave() const;
    void append(GLArrayBuffer* buffer, void* source, size_t size, size_t count = 1);

protected:
    
    struct BufferAttribute
    {
        GLArrayBuffer* _buffer;
        VertexStreamAttribute _stream;
    };
    std::map<int, BufferAttribute> _vertexStreams;

    IndexBuffer* _indices;

    size_t _count;
    bool _interleaved;
    bool _dirty;
    int _vao;
    
    Primitive _drawingPrimitive;

    EventListenerCustom* _recreateEventListener;
};

NS_CC_END

#endif //__CC_VERTEX_INDEX_DATA_H__
