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

#ifndef __CC_PRIMITIVE_H__
#define __CC_PRIMITIVE_H__

#include "renderer/CCVertexIndexData.h"

NS_CC_BEGIN

class IndexBuffer;

class CC_DLL Primitive : public Ref
{
public:
    static Primitive* create(VertexData* verts, IndexBuffer* indices, int type);
    
    const VertexData* getVertexData() const;
    
    const IndexBuffer* getIndexData() const;
    
    int getType() const { return _type; }
    
    //called by rendering framework
    void draw();
    
    int getStart() const { return _start; }
    int getCount() const { return _count; }
    void setStart(int start) { _start = start; }
    void setCount(int count) { _count = count; }
    
protected:
    Primitive();
    virtual ~Primitive();
    
    bool init(VertexData* verts, IndexBuffer* indices, int type);
    
protected:
    VertexData* _verts;
    IndexBuffer* _indices;
    int _start;
    int _count;
    int _type;
};

NS_CC_END

#endif //__CC_PRIMITIVE_H__
