
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

#ifndef __CC_VERTEX_INDEX_DATA_H__
#define __CC_VERTEX_INDEX_DATA_H__

#include <map>
#include <set>
#include "base/CCRef.h"
#include "renderer/CCVertexAttribute.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN

class GLArrayBuffer;
class IndexBuffer;
class EventListenerCustom;

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
    static T* create(Primitive primitive = Triangles)
    {
        auto result = new (std::nothrow) T(primitive);
        if (result)
        {
            result->autorelease();
            return result;
        }
        return nullptr;
    }

    virtual ~VertexData();
    
    // @brief Return the number of vertex streams
    ssize_t getVertexStreamCount() const;
    
    // @brief add vertex stream descriptors to a buffer 
    CC_DEPRECATED(v3) bool setStream(GLArrayBuffer* buffer, const VertexAttribute& stream) { return addStream(buffer, stream); }
    bool addStream(GLArrayBuffer* vertices, const VertexAttribute& stream);
    void removeStream(int semantic);
    
    // @brief specify indexed drawing for vertex data
    void setIndexBuffer(IndexBuffer* indices);
    void removeIndexBuffer();
    
    const VertexAttribute* getStreamAttribute(int semantic) const;
    VertexAttribute* getStreamAttribute(int semantic);
        
    // @brief update and draw the buffer.
    ssize_t draw(ssize_t start = 0, ssize_t count = 0);
    
    // @brief true/false if all vertex buffers are empty
    bool empty() const;
    
    // @brief clears the vertex buffers associated with this vertex data
    void clear();
    
    // @brief returns the count of vertices added
    ssize_t getCount() const;
    
    // @brief returns the capacity of the buffer in bytes
    ssize_t getCapacity() const;

    // @brief returns the dirty status of the data or vertex streams
    bool isDirty() const;
    
    // @brief sets the dirty state of all vertex data
    void setDirty(bool dirty);
    
    template <typename T>
    void append(const T& vertex)
    {
        if (_interleaved)
        {
            for (auto& e : _vertexStreams)
            {
                auto const verts = e.second._buffer;
                append(verts, (void*)&vertex, 1);
                return;
            }
        }
        else
        {
            for (auto& e : _vertexStreams)
            {
                auto const verts = e.second._buffer;
                intptr_t p = (intptr_t)&vertex + e.second._stream._offset;
                append(verts, (void*)p, 1);
            }
        }
    }

    void recreate() const;

protected:

    VertexData(Primitive primitive);
    
    bool determineInterleave() const;
    void append(GLArrayBuffer* buffer, void* source, ssize_t count = 1);
    int DataTypeToGL(DataType type);

protected:
    
    struct BufferAttribute
    {
        GLArrayBuffer* _buffer;
        VertexAttribute _stream;
    };
    std::map<int, BufferAttribute> _vertexStreams;

    // unique set of buffers. For interleaved data there should be only one
    // in theory you may be able to have two sets of interleaved data but I
    // think in that case, using two separate VertexData instances is best.
    typedef std::set<GLArrayBuffer*> tBuffers;
    tBuffers _buffers;
    
    IndexBuffer* _indices;

    bool _interleaved;
    bool _dirty;
    int _vao;
    
    Primitive _drawingPrimitive;

    EventListenerCustom* _recreateEventListener;
};

NS_CC_END

#endif //__CC_VERTEX_INDEX_DATA_H__
