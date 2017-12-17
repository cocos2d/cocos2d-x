/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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
VertexBuffer is an abstraction of low level openGL Vertex Buffer Object.
It is used to save an array of vertices.
*@js NA
*/
class CC_DLL VertexBuffer : public Ref
{
public:
    /**
    Create an instance of VertexBuffer.
    @param sizePerVertex Size in bytes of one vertex.
    @param vertexNumber The number of vertex.
    @param usage A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
    */
    static VertexBuffer* create(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
    /**Get the size in bytes of one vertex.*/
    int getSizePerVertex() const;
    /**Get the number of vertices.*/
    int getVertexNumber() const;
    /**
    Update all or part of vertices data, if the range specified exceeds the vertex buffer, it will be clipped.
    @param verts The pointer of the vertex data.
    @param count The number of vertices to update.
    @param begin The first vertex to update.
    */
    bool updateVertices(const void* verts, int count, int begin);

    /**
    Get the size of the vertex array in bytes, equals getSizePerVertex() * getVertexNumber().
    */
    int getSize() const;
    /**
    Get the internal openGL handle.
    */
    GLuint getVBO() const;
    
protected:
    /**
    Constructor.
    */
    VertexBuffer();
    /**
    Destructor.
    */
    virtual ~VertexBuffer();
    /**
    Init the storage of vertex buffer.
    @param sizePerVertex Size in bytes of one vertex.
    @param vertexNumber The number of vertex.
    @param usage A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
    */
    bool init(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
protected:
    /**
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
protected:
    /**
    Internal handle for openGL.
    */
    mutable GLuint _vbo;
    /**
    Size in bytes for one vertex.
    */
    int _sizePerVertex;
    /**
    Number of vertices.
    */
    int _vertexNumber;
    /**
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**
    Static member to indicate that use _shadowCopy or not. 
    */
    static bool _enableShadowCopy;
public:
    /**
    Static getter for shadowCopy.
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**
     Static setter for shadowCopy.
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};

/**
IndexBuffer is an abstraction of low level openGL Buffer Object.
It used to save an array of indices.
@js NA
*/
class CC_DLL IndexBuffer : public Ref
{
public:
    /**
    Enum for the type of index, short indices and int indices could be used.
    */
    enum class IndexType
    {
        /**Short index will be used.*/
        INDEX_TYPE_SHORT_16,
        /**Int index will be used.*/
        INDEX_TYPE_UINT_32
    };
    
public:
    /**
    Create an instance of IndexBuffer.
    @param type type of index.
    @param number The number of indices.
    @param usage A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
    */
    static IndexBuffer* create(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    /**
    Getter for type of indices.
    */
    IndexType getType() const;
    /**
    Get the size in bytes for one index, will be 2 for INDEX_TYPE_SHORT_16 and 4 for INDEX_TYPE_UINT_32.
    */
    int getSizePerIndex() const;
    /**
    Get the number of indices.
    */
    int getIndexNumber() const;
    /**
    Update all or part of indices data, if the range specified exceeds the vertex buffer, it will be clipped.
    @param indices The pointer of the index data.
    @param count The number of indices to update.
    @param begin The start index to update.
    */
    bool updateIndices(const void* indices, int count, int begin);
    /**
    Get the size in bytes of the array of indices.
    */
    int getSize() const;
    /**
    Get the openGL handle for index buffer.
    */
    GLuint getVBO() const;

protected:
    /**
    Constructor.
    */
    IndexBuffer();
    /**
    Destructor.
    */
    virtual ~IndexBuffer();
    /**
    Init the storageof IndexBuffer.
    @param type type of index.
    @param number The number of indices.
    @param usage A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
    */
    bool init(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    
protected:
    /**
    Handle for openGL.
    */
    mutable GLuint _vbo;
    /**
    Type for index.
    */
    IndexType _type;
    /**
    Number of indices.
    */
    int _indexNumber;
    
protected:
    /**
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
    /**
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**
    Static member to indicate that use _shadowCopy or not.
    */
    static bool _enableShadowCopy;
public:
    /**
    Static getter for shadowCopy.
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**
     Static setter for shadowCopy.
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};


NS_CC_END

/**
 end of support group
 @}
 */
#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
