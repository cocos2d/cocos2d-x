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

#ifndef __CC_VERTEX_INDEX_DATA_H__
#define __CC_VERTEX_INDEX_DATA_H__

#include "base/CCRef.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCMap.h"
#include <map>

NS_CC_BEGIN

class VertexBuffer;

enum class VertexSemantic
{
    UNKNOWN,
    POSITION,
    COLOR,
    NORMAL,
    BLEND_WEIGHT,
    BLEND_INDEX,
    TEXTURECOORD0,
    TEXTURECOORD1,
    TEXTURECOORD2,
    TEXTURECOORD3
};

enum class VertexType
{
    UNKNOWN,
    FLOAT1,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    BYTE4
};

struct VertexStreamAttribute
{
    VertexStreamAttribute()
    : _index(-1), _offset(0),_semantic(VertexSemantic::UNKNOWN),_type(VertexType::UNKNOWN)
    {
    }
    int _index;
    int _offset;
    VertexSemantic _semantic;
    VertexType _type;
};

class VertexData : public Ref
{
public:
    static VertexData* create();
    
    size_t getVertexStreamCount() const;
    bool setStream(int index, VertexBuffer* buffer, const VertexStreamAttribute& stream);
    void removeStream(int index);
    const VertexStreamAttribute* getStreamAttribute(int index) const;
    VertexStreamAttribute* getStreamAttribute(int index);
    
    VertexBuffer* getStreamBuffer(int index) const;
    
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

class IndexData : public Ref
{
public:
    static IndexData* create(IndexBuffer* buffer, int start, int count);
    
protected:
    IndexData();
    virtual ~IndexData();
    
    void init(IndexBuffer* buffer, int start, int count);
protected:
    IndexBuffer* _buffer;
public:
    int _offset;
    int _count;
};

NS_CC_END

#endif //__CC_VERTEX_INDEX_DATA_H__
