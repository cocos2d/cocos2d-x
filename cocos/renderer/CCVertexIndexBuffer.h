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

#ifndef __CC_VERTEX_INDEX_BUFFER_H__
#define __CC_VERTEX_INDEX_BUFFER_H__

#include <vector>
#include "base/CCRef.h"
#include "platform/CCGL.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class EventListenerCustom;

/**
@class VertexBuffer
@brief
@~english
VertexBuffer is an abstraction of low level openGL Vertex Buffer Object.
It is used to save an array of vertices.
 * @~chinese 
VertexBuffer是openGL底层的顶点缓冲VBO的抽象，用来存在一组顶点数据。
*@js NA
*/
class CC_DLL VertexBuffer : public Ref
{
public:
    /**@~english
    Create an instance of VertexBuffer.
     * @~chinese 
     * 创建VertexBuffer的一个实例。
    @param sizePerVertex @~english Size in bytes of one vertex.
     * @~chinese 一个顶点的字节数。
    @param vertexNumber @~english The number of vertex.
     * @~chinese 顶点的个数。
    @param usage @~english A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
     * @~chinese 给底层驱动的标示，表明VertexBuffer是否经常更新，这样可以潜在的让openGL优化其性能。
    */
    static VertexBuffer* create(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
    /**
    @~english Get the size in bytes of one vertex. 
    @~chinese 得到一个顶点的字节数。
    */
    int getSizePerVertex() const;
    /**
    @~english Get the number of vertices. 
    @~chinese 得到顶点的数量。
    */
    int getVertexNumber() const;
    /**@~english
    Update all or part of vertices data, if the range specified exceeds the vertex buffer, it will be clipped.
     * @~chinese 
     * 更新所有或部分顶点数据,如果指定的范围超过了顶点缓冲区,它将被截断。
    @param verts @~english The pointer of the vertex data.
     * @~chinese 顶点数据的指针。
    @param count @~english The number of vertices to update.
     * @~chinese 顶点更新的数量。
    @param begin @~english The first vertex to update.
     * @~chinese 要更新的第一个顶点的位置。
    */
    bool updateVertices(const void* verts, int count, int begin);

    /**@~english
    Get the size of the vertex array in bytes, equals getSizePerVertex() * getVertexNumber().
     * @~chinese 
     * 得到整个vertexBuffer中所有顶点的大小，以字节为单位，等同于getSizePerVertex() * getVertexNumber()。
    */
    int getSize() const;
    /**@~english
    Get the internal openGL handle.
     * @~chinese 
     * 得到内部openGL句柄。
    */
    GLuint getVBO() const;
    
protected:
    /**@~english
    Constructor.
    @~chinese 构造函数。
    */
    VertexBuffer();
    /**@~english
    Destructor.
    @~chinese 析构函数。
    */
    virtual ~VertexBuffer();
    /**@~english
    Init the storage of vertex buffer.
     * @~chinese 
     * 初始化存储顶点缓冲区。
    @param sizePerVertex @~english Size in bytes of one vertex.
     * @~chinese 一个顶点的字节数。
    @param vertexNumber @~english The number of vertex.
     * @~chinese 顶点的个数。
    @param usage @~english A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
     * @~chinese 给底层驱动的标示，表明VertexBuffer是否经常更新，这样可以潜在的让openGL优化其性能。
    */
    bool init(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
protected:
    /**@~english
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**@~english
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
protected:
    /**@~english
    Internal handle for openGL.
    */
    mutable GLuint _vbo;
    /**@~english
    Size in bytes for one vertex.
    */
    int _sizePerVertex;
    /**@~english
    Number of vertices.
    */
    int _vertexNumber;
    /**@~english
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**@~english
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**@~english
    Static member to indicate that use _shadowCopy or not. 
    if it is true, a memory copy is used to update the openGL resource, 
    used for platform when GL context could be lost, such as android.
    */
    static bool _enableShadowCopy;
public:
    /**@~english
    Static getter for shadowCopy.
     * @~chinese 
     * 得到ShdowCopy的开启状态，如果开启，那么需要在内存保存一份数据来更新openGL资源。
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**@~english
     Static setter for shadowCopy.
     * @~chinese 
     * 设置ShdowCopy的开启状态，如果开启，那么需要在内存保存一份数据来更新openGL资源。
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};

/**
@class IndexBuffer
@brief
@~english
IndexBuffer is an abstraction of low level openGL Buffer Object.
It used to save an array of indices.
 * @~chinese 
 * 与VertexBuffer，IndexBuffer也是底层openGL索引缓冲的封装。
 * 它用于保存索引数组。
@js NA
*/
class CC_DLL IndexBuffer : public Ref
{
public:
    /**@~english
    Enum for the type of index, short indices and int indices could be used.
     * @~chinese 
     * 枚举类型的指数,每一个索引可能是short和int类型。
    */
    enum class IndexType
    {
        /**@~english Short index will be used. @~chinese 将使用short作为索引。*/
        INDEX_TYPE_SHORT_16,
        /**@~english Int index will be used. @~chinese 将使用Int作为索引。*/
        INDEX_TYPE_UINT_32
    };
    
public:
    /**@~english
    Create an instance of IndexBuffer.
     * @~chinese 
     * 创建一个IndexBuffer实例。
    @param type @~english type of index.
     * @~chinese 索引的类型。
    @param number @~english The number of indices.
     * @~chinese 索引的数量。
    @param usage @~english A hint to indicate whether the indexBuffer are updated frequently or not to let GL optimise it.
     @~chinese 给底层驱动的标示，表明indexBuffer是否经常更新，这样可以潜在的让openGL优化其性能。
    */
    static IndexBuffer* create(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    /**@~english
    Getter for type of indices.
     * @~chinese 
     * 得到索引的类型。
    */
    IndexType getType() const;
    /**@~english
    Get the size in bytes for one index, will be 2 for INDEX_TYPE_SHORT_16 and 4 for INDEX_TYPE_UINT_32.
     * @~chinese 
     * 获得一个索引的大小(以字节为单位）,short类型的返回2，int类型的返回4。
    */
    int getSizePerIndex() const;
    /**@~english
    Get the number of indices.
     * @~chinese 
     * 得到索引的数量。
    */
    int getIndexNumber() const;
    /**@~english
    Update all or part of indices data, if the range specified exceeds the vertex buffer, it will be clipped.
     * @~chinese 
     * 更新所有或部分指数数据,如果指定的范围超过了顶点缓冲区,它将被截断。
    @param indices @~english The pointer of the index data.
     * @~chinese 索引数据的指针。
    @param count @~english The number of indices to update.
     * @~chinese 要更新的索引个数.
    @param begin @~english The start index to update.
     * @~chinese 第一个要更新的索引位置。
    */
    bool updateIndices(const void* indices, int count, int begin);
    /**@~english
    Get the size in bytes of the array of indices.
     * @~chinese 
     * 得到所有索引的大小，以字节为单位。
    */
    int getSize() const;
    /**@~english
    Get the openGL handle for index buffer.
     * @~chinese 
     * 获得内部openGL句柄。
    */
    GLuint getVBO() const;

protected:
    /**@~english
    Constructor.
     * @~chinese 
     * 构造函数。
    */
    IndexBuffer();
    /**@~english
    Destructor.
     * @~chinese 
     * 析构函数。
    */
    virtual ~IndexBuffer();
    /**@~english
    Init the storage of IndexBuffer.
     * @~chinese 
     * 初始化IndexBuffer的存储。
    @param type @~english type of index.
     * @~chinese 索引的类型。
    @param number @~english The number of indices.
     * @~chinese 索引的数量。
    @param usage @~english A hint to indicate whether the indexBuffer are updated frequently or not to let GL optimise it.
     @~chinese 给底层驱动的标示，表明indexBuffer是否经常更新，这样可以潜在的让openGL优化其性能。
    */
    bool init(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    
protected:
    /**@~english
    Handle for openGL.
    */
    mutable GLuint _vbo;
    /**@~english
    Type for index.
    */
    IndexType _type;
    /**@~english
    Number of indices.
    */
    int _indexNumber;
    
protected:
    /**@~english
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**@~english
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
    /**@~english
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**@~english
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**@~english
    Static member to indicate that use _shadowCopy or not. 
    if it is true, a memory copy is used to update the openGL resource, 
    used for platform when GL context could be lost, such as android.
    */
    static bool _enableShadowCopy;
public:
    /**@~english
    Static getter for shadowCopy.
     * @~chinese 
     * 得到ShdowCopy的开启状态，如果开启，那么需要在内存保存一份数据来更新openGL资源。
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**@~english
     Static setter for shadowCopy.
     * @~chinese 
     * 设置ShdowCopy的开启状态，如果开启，那么需要在内存保存一份数据来更新openGL资源。
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};


NS_CC_END

/**
 end of support group
 @}
 */
#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
