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

#include "3d/CCBundle3DData.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN

class EventListenerCustom;
class EventCustom;

class RenderMeshData
{
    friend class Mesh;
public:
    RenderMeshData(): _vertexsizeBytes(0)
    {
    }
    bool hasVertexAttrib(int attrib);
    bool init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);
    bool init(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<unsigned short>& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount);
    
protected:
    
    int calVertexSizeBytes();
    
    int _vertexsizeBytes;
    ssize_t _vertexNum;
    std::vector<float> _vertexs;
    std::vector<unsigned short> _indices;
    std::vector<MeshVertexAttrib> _vertexAttribs;
};

/** 
 * Mesh: Geometry with a collection of vertex. 
 * Supporting various vertex formats.
 */
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

    /**create mesh from positions, normals, and so on*/
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);
    
    /**create mesh with vertex attributes*/
    static Mesh* create(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<unsigned short>& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount);

    /**get vertex buffer*/
    inline GLuint getVertexBuffer() const { return _vertexBuffer; }
    
    /**get mesh vertex attribute count*/
    ssize_t getMeshVertexAttribCount() const { return _renderdata._vertexAttribs.size(); }
    /**get MeshVertexAttribute by index*/
    const MeshVertexAttrib& getMeshVertexAttribute(int idx) const { return _renderdata._vertexAttribs[idx]; }
    /**has vertex attribute?*/
    bool hasVertexAttrib(int attrib) { return _renderdata.hasVertexAttrib(attrib); }
    /**get per vertex size in bytes*/
    int getVertexSizeInBytes() const { return _renderdata._vertexsizeBytes; }
    
    /** get primitive type*/
    PrimitiveType getPrimitiveType() const { return _primitiveType; }
    /**get index count*/
    ssize_t getIndexCount() const { return _indexCount; }
    /**get index format*/
    IndexFormat getIndexFormat() const { return _indexFormat; }
    /**get index buffer*/
    GLuint getIndexBuffer() const {return _indexBuffer; }
    
    /**build vertex buffer from renderdata*/
    void restore();

CC_CONSTRUCTOR_ACCESS:
    
    Mesh();
    virtual ~Mesh();
    /**init mesh*/
    bool init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices);
    
    /**init mesh*/
    bool init(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<unsigned short>& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount);

    /**build buffer*/
    void buildBuffer();
    /**free buffer*/
    void cleanAndFreeBuffers();

protected:
    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    ssize_t _indexCount;

    RenderMeshData _renderdata;
};

/**
 * Mesh Cache
 */
class MeshCache
{
public:
    /**get & destroy*/
    static MeshCache* getInstance();
    static void destroyInstance();
    
    /**get mesh from cache*/
    Mesh* getMesh(const std::string& key) const;
    
    /**add mesh to cache*/
    bool addMesh(const std::string& key, Mesh* mesh);
    
    /**remove all meshes*/
    void removeAllMeshes();

    /**remove unused meshes*/
    void removeUnusedMesh();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void listenBackToForeground(EventCustom* event);
#endif
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshCache();
    ~MeshCache();
    
protected:
    
    static MeshCache* _cacheInstance;//instance
    
    std::unordered_map<std::string, Mesh*> _meshes; //cached meshes
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    EventListenerCustom* _backToForegroundlistener;
#endif
};

NS_CC_END

#endif // __CCMESH_H_
