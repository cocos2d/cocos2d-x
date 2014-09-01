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

class VertexBuffer;

struct CC_DLL VertexStreamAttribute
{
    VertexStreamAttribute()
    : _offset(0),_semantic(0),_type(0),_size(0), _normalize(false)
    {
    }

    VertexStreamAttribute(int offset, int semantic, int type, int size)
    : _offset(offset),_semantic(semantic),_type(type),_size(size), _normalize(false)
    {
    }
    
    VertexStreamAttribute(int offset, int semantic, int type, int size, bool normalize)
    : _offset(offset),_semantic(semantic),_type(type),_size(size), _normalize(normalize)
    {
    }
    
    bool _normalize;
    int _offset;
    int _semantic;
    int _type;
    int _size;
};

class CC_DLL VertexData : public Ref
{
public:
    static VertexData* create();
    
    size_t getVertexStreamCount() const;
    bool setStream(VertexBuffer* buffer, const VertexStreamAttribute& stream);
    void removeStream(int semantic);
    const VertexStreamAttribute* getStreamAttribute(int semantic) const;
    VertexStreamAttribute* getStreamAttribute(int semantic);
    
    VertexBuffer* getStreamBuffer(int semantic) const;
    
    void use();
protected:
    VertexData();
    virtual ~VertexData();
protected:
    struct BufferAttribute
    {
        VertexBuffer* _buffer;
        VertexStreamAttribute _stream;
    };
    
    std::map<int, BufferAttribute> _vertexStreams;
};

NS_CC_END

#endif //__CC_VERTEX_INDEX_DATA_H__
