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
#include "3d/CCSubMesh.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN

class EventListenerCustom;
class EventCustom;

class CC_DLL RenderMeshData
{
    typedef std::vector<unsigned short> IndexArray;
    friend class Mesh;
public:
    RenderMeshData(): _vertexsizeBytes(0)
    {
    }
    bool hasVertexAttrib(int attrib);
    bool init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<IndexArray>& subMeshIndices);
    bool init(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<IndexArray>& subMeshIndices, const std::vector<MeshVertexAttrib>& attribs);
    
protected:
    
    int calVertexSizeBytes();
    
    int _vertexsizeBytes;
    ssize_t _vertexNum;
    std::vector<float> _vertexs;
    std::vector<IndexArray> _subMeshIndices;
    std::vector<MeshVertexAttrib> _vertexAttribs;
};

/** 
 * Mesh: Geometry with a collection of vertex. 
 * Supporting various vertex formats.
 */
class CC_DLL Mesh : public Ref
{
    typedef std::vector<unsigned short> IndexArray;
public:
    /**create mesh from positions, normals, and so on, sigle SubMesh*/
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices);
    
    /**create mesh from positions, normals, and so on, multi-SubMesh*/
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<IndexArray>& subMeshIndices);
    
    /**create mesh with vertex attributes*/
    CC_DEPRECATED_ATTRIBUTE static Mesh* create(const std::vector<float>& vertices, int vertexSizeInFloat, const IndexArray& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount) { return create(vertices, vertexSizeInFloat, indices, attribs); }
    
    /**
     * create Mesh
     * @param vertices vertices buffer data
     * @param vertexSizeInFloat size of each vertex
     * @param indices index buffer data that denotes how to connect the vertex, sigle SubMesh
     * @param attribs vertex attributes
     */
    static Mesh* create(const std::vector<float>& vertices, int vertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs);
    
    /**
     * create Mesh
     * @param vertices vertices buffer data
     * @param vertexSizeInFloat size of each vertex
     * @param subMeshIndices index buffer data that denotes how to connect the vertex, multi-SubMesh
     * @param attribs vertex attributes
     */
    static Mesh* create(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<IndexArray>& subMeshIndices, const std::vector<MeshVertexAttrib>& attribs);

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
    
    /**get sub mesh count*/
    ssize_t getSubMeshCount() const { return _subMeshes.size(); }
    
    /**get sub mesh by index*/
    SubMesh* getSubMesh(int index) const { return _subMeshes.at(index); }
    
    /**build vertex buffer from renderdata*/
    void restore();
    
    /**to be deprecated, those functions have been moved to SubMesh*/
    /** get primitive type*/
    CC_DEPRECATED_ATTRIBUTE PrimitiveType getPrimitiveType() const { return _subMeshes.at(0)->getPrimitiveType(); }
    /**get index count*/
    CC_DEPRECATED_ATTRIBUTE ssize_t getIndexCount() const { return _subMeshes.at(0)->getIndexCount(); }
    /**get index format*/
    CC_DEPRECATED_ATTRIBUTE IndexFormat getIndexFormat() const { return _subMeshes.at(0)->getIndexFormat(); }
    /**get index buffer*/
    CC_DEPRECATED_ATTRIBUTE GLuint getIndexBuffer() const {return _subMeshes.at(0)->getIndexBuffer(); }

CC_CONSTRUCTOR_ACCESS:
    
    Mesh();
    virtual ~Mesh();
    /**init mesh*/
    bool init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<IndexArray>& indices);
    
    /**init mesh*/
    bool init(const std::vector<float>& vertices, int vertexSizeInFloat, const std::vector<IndexArray>& indices, const std::vector<MeshVertexAttrib>& attribs);

    /**build sub meshes*/
    void buildSubMeshes();
    /**build buffer*/
    void buildBuffer();
    /**free buffer*/
    void cleanAndFreeBuffers();

protected:
    GLuint _vertexBuffer;
    Vector<SubMesh*> _subMeshes;

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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    void listenRendererRecreated(EventCustom* event);
#endif
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshCache();
    ~MeshCache();
    
protected:
    
    static MeshCache* _cacheInstance;//instance
    
    std::unordered_map<std::string, Mesh*> _meshes; //cached meshes
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

NS_CC_END

#endif // __CCMESH_H_
