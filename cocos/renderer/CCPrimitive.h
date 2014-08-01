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

#ifndef __CC_PRIMITIVE_H__
#define __CC_PRIMITIVE_H__

#include "renderer/CCVertexIndexData.h"

NS_CC_BEGIN
enum class PrimitiveType
{
    POINTS,
    LINES,
    TRIANGLES
};

class Primitive : public Ref
{
public:
    static Primitive* create(VertexData* verts, IndexData* indices, PrimitiveType type);
    
    VertexData* getVertexData();
    
    IndexData* getIndexData();
    
    PrimitiveType getType() const { return _type; }
    
    //called by rendering framework
    void draw();
protected:
    Primitive();
    virtual ~Primitive();
    
    bool init(VertexData* verts, IndexData* indices, PrimitiveType type);
    
protected:
    VertexData* _verts;
    IndexData* _indices;
    PrimitiveType _type;
};

NS_CC_END

#endif //__CC_PRIMITIVE_H__
