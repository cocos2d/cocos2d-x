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

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN

class IndexBuffer;

/**
 Primitive can support sending points, lines and triangles to glpipeline, which is an abstraction
 of primitive data.
 */
class CC_DLL Primitive : public Ref
{
public:
    /**
     Create an instance of primitive.
     @param verts VertexData used in the primitive.
     @param indices Optional index data.
     @param type The type (Points, Lines, Triangles) used.
     */
    static Primitive* create(VertexData* verts, IndexBuffer* indices, int type);
    /**Get the vertexData.*/
    const VertexData* getVertexData() const;
    /**Get the optional index data, will return null if index data is not used.*/
    const IndexBuffer* getIndexData() const;
    /**Get the primitive type.*/
    int getType() const { return _type; }
    
    /**called by rendering framework, will send the data to GLPipeline.*/
    void draw();
    
    /**Get the start index of primtive.*/
    int getStart() const { return _start; }
    /**Get the number of vertices or indices used for drawing.*/
    int getCount() const { return _count; }
    /**Setter for the start index.*/
    void setStart(int start) { _start = start; }
    /**Setter for the count. */
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

/**
 end of support group
 @}
 */
#endif //__CC_PRIMITIVE_H__
