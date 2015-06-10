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

/**@class Primitive
@brief
@~english
 Primitive can support sending points, lines and triangles to glpipeline, which is an abstraction
 of primitive data.
 * @~chinese 
 * Primitive可以支持点,线和三角形的渲染, 是渲染基础图元的抽象。
 */
class CC_DLL Primitive : public Ref
{
public:
    /**@~english
     Create an instance of primitive.
     * @~chinese 
     * 创建一个Primitive实例。
     @param verts @~english VertexData used in the primitive.
     * @~chinese 图元使用的VertexData。
     @param indices @~english Optional index data, null will means that no indices needed.
     * @~chinese 索引缓冲，如果是null，表示没有索引。
     @param type @~english The type (Points, Lines, Triangles) used.
     * @~chinese openGL中枚举的图元类型(点、线、三角形)。
     */
    static Primitive* create(VertexData* verts, IndexBuffer* indices, int type);
    /**@~english Get the vertexData. @~chinese 得到VertexData。*/
    const VertexData* getVertexData() const;
    /**@~english Get the optional index data, will return null if index data is not used. @~chinese 可选的索引数据,如果不使用索引数据将返回null。*/
    const IndexBuffer* getIndexData() const;
    /**@~english Get the primitive type. @~chinese 图元的类型。*/
    int getType() const { return _type; }
    
    /**@~english called by rendering framework, will send the data to GLPipeline. @~chinese 被渲染框架,将向GLPipeline发送数据。*/
    void draw();
    
    /**@~english Get the start index of primtive. @~chinese 绘制的起始索引位置。*/
    int getStart() const { return _start; }
    /**@~english Get the number of vertices or indices used for drawing. @~chinese 用于绘制的顶点或者索引（如果有）的数目。*/
    int getCount() const { return _count; }
    /**@~english Setter for the start index. @~chinese 设置开始索引的位置。*/
    void setStart(int start) { _start = start; }
    /**@~english Setter for the count.  @~chinese 设置绘制的顶点或索引的个数。*/
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
