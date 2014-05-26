/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCMESH_H__
#define __CCMESH_H__

#include <string>
#include <vector>

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN

//mesh vertex attribute
struct MeshVertexAttrib
{
    //attribute size
    GLint size;
    //GL_FLOAT
    GLenum type;
    //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, GLProgram for detail
    int  vertexAttrib;
    //size in bytes
    int attribSizeBytes;
};

class RenderMeshData
{
    friend class Mesh;
public:
    RenderMeshData(): _vertexsizeBytes(0)
    {
    }
    bool hasVertexAttrib(int attrib);
    bool initFrom(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);
    
protected:
    int _vertexsizeBytes;
    ssize_t _vertexNum;
    std::vector<float> _vertexs;
    std::vector<unsigned short> _indices;
    std::vector<MeshVertexAttrib> _vertexAttribs;
};

/** Mesh: TODO, add description of Mesh */
class Mesh : public Ref
{
public:
    /** Defines supported index formats. */
    enum class IndexFormat
    {
        INDEX8 = GL_UNSIGNED_BYTE,
        INDEX16 = GL_UNSIGNED_SHORT,
    };

    /** Defines supported primitive types. */
    enum class PrimitiveType
    {
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        LINES = GL_LINES,
        LINE_STRIP = GL_LINE_STRIP,
        POINTS = GL_POINTS
    };

    //create
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);

    //get vertex buffer
    inline GLuint getVertexBuffer() const { return _vertexBuffer; }
    
    //get mesh vertex attribute count
    ssize_t getMeshVertexAttribCount() const { return _renderdata._vertexAttribs.size(); }
    //get MeshVertexAttribute by index
    const MeshVertexAttrib& getMeshVertexAttribute(int idx) const { return _renderdata._vertexAttribs[idx]; }
    //has vertex attribute?
    bool hasVertexAttrib(int attrib) { return _renderdata.hasVertexAttrib(attrib); }
    //get per vertex size in bytes
    int getVertexSizeInBytes() const { return _renderdata._vertexsizeBytes; }
    
    PrimitiveType getPrimitiveType() const { return _primitiveType; }
    ssize_t getIndexCount() const { return _indexCount; }
    IndexFormat getIndexFormat() const { return _indexFormat; }
    GLuint getIndexBuffer() const {return _indexBuffer; }
    
    //build vertex buffer from renderdata
    void restore();

protected:
    Mesh();
    virtual ~Mesh();
    bool init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);

    //build buffer
    void buildBuffer();
    void cleanAndFreeBuffers();

    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    ssize_t _indexCount;

    RenderMeshData _renderdata;
};

NS_CC_END

#endif // __CCMESH_H_
