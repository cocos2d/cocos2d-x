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

#include "3d/CCBundle3DData.h"
#include "3d/CCAABB.h"

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

class Texture2D;
class MeshSkin;
class MeshIndexData;
class GLProgramState;
class GLProgram;
/** 
 * Mesh: contains ref to index buffer, GLProgramState, texture, skin, blend function, aabb and so on
 */
class CC_DLL Mesh : public Ref
{
    friend class Sprite3D;
public:
    typedef std::vector<unsigned short> IndexArray;
    /**create mesh from positions, normals, and so on, sigle SubMesh*/
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices);
    /**create mesh with vertex attributes*/
    CC_DEPRECATED_ATTRIBUTE static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount){ return create(vertices, perVertexSizeInFloat, indices, attribs); }
    
    static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs);
    
    /** create mesh */
    static Mesh* create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin = nullptr);
    
    /**get vertex buffer*/
    GLuint getVertexBuffer() const;
    /**has vertex attribute?*/
    bool hasVertexAttrib(int attrib) const;
    /**get mesh vertex attribute count*/
    ssize_t getMeshVertexAttribCount() const;
    /**get MeshVertexAttribute by index*/
    const MeshVertexAttrib& getMeshVertexAttribute(int idx);
    /**get per vertex size in bytes*/
    int getVertexSizeInBytes() const;

    /**texture getter and setter*/
    void setTexture(const std::string& texPath);
    void setTexture(Texture2D* tex);
    Texture2D* getTexture() const { return _texture; }
    
    /**visible getter and setter*/
    void setVisible(bool visible);
    bool isVisible() const { return _visible; }
    
    /**skin getter */
    MeshSkin* getSkin() const { return _skin; }
    
    /**mesh index data getter */
    MeshIndexData* getMeshIndexData() const { return _meshIndexData; }
    
    /**get GLProgramState*/
    GLProgramState* getGLProgramState() const { return _glProgramState; }
    
    /**name getter */
    const std::string& getName() const { return _name; }
    
    void setBlendFunc(const BlendFunc &blendFunc);
    const BlendFunc &getBlendFunc() const;
    
    /** get primitive type*/
    GLenum getPrimitiveType() const;
    /**get index count*/
    ssize_t getIndexCount() const;
    /**get index format*/
    GLenum getIndexFormat() const;
    /**get index buffer*/
    GLuint getIndexBuffer() const;
    
    /**get AABB*/
    const AABB& getAABB() const { return _aabb; }

CC_CONSTRUCTOR_ACCESS:
    
    Mesh();
    virtual ~Mesh();
    
    GLProgram* getDefaultGLProgram(bool textured);
    
    void setGLProgramState(GLProgramState* glProgramState);
    
    MeshCommand& getMeshCommand() { return _meshCommand; }

    /**skin setter*/
    void setSkin(MeshSkin* skin);
    /**Mesh index data setter*/
    void setMeshIndexData(MeshIndexData* indexdata);
    /**name setter*/
    void setName(const std::string& name) { _name = name; }
 
    void calcuateAABB();
    
    void bindMeshCommand();
protected:
    Texture2D* _texture;  //texture that submesh is using
    MeshSkin*  _skin;     //skin
    bool       _visible; // is the submesh visible
    bool       _isTransparent; // is this mesh transparent, it is a property of material in fact
    
    std::string  _name;
    MeshIndexData*     _meshIndexData;
    GLProgramState* _glProgramState;
    MeshCommand     _meshCommand;
    BlendFunc       _blend;
    AABB         _aabb;
    std::function<void()> _visibleChanged;
};

NS_CC_END

#endif // __CCMESH_H__
