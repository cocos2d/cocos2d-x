
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

#ifndef __CC_BATCH_H__
#define __CC_BATCH_H__

#include "renderer/CCVertexIndexData.h"

NS_CC_BEGIN

class IndexBuffer;

class CC_DLL Batch : public Ref
{
public:
 
    template <class T>
    T* create(VertexData* verts, IndexBuffer* indices, int drawingPrimitive)
    {
        auto result = new (std::nothrow) T;
        if (result && result->init(verts, indices, drawingPrimitive))
        {
            result->autorelease();
            return result;
        }
        delete result;
        return  nullptr;
    }
 
    Batch();
    virtual ~Batch();

    bool init(VertexData* verts, IndexBuffer* indices, int drawingPrimitive);

    const VertexData* getVertexData() const;
    const IndexBuffer* getIndexData() const;
    
    CC_DEPRECATED_ATTRIBUTE int getType() const { return _drawingPrimitive; }
    int getDrawingPrimitive() const { return _drawingPrimitive; }
    
    void draw();
    
    int getStart() const { return _start; }
    int getCount() const { return _count; }
    void setStart(int start) { _start = start; }
    void setCount(int count) { _count = count; }
    
protected:

    VertexData* _verts;
    IndexBuffer* _indices;
    int _start;
    int _count;
    int _drawingPrimitive;
};

NS_CC_END

#endif //__CC_PRIMITIVE_H__
