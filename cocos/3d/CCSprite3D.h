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

#ifndef __CCSPRITE3D_H__
#define __CCSPRITE3D_H__

#include <vector>
#include <unordered_map>

#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCMeshCommand.h"
#include "CCAABB.h"
#include "3d/3dExport.h"

NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Texture2D;
class MeshSkin;
class AttachNode;
class SubMeshState;
class Skeleton3D;

/** Sprite3D: A sprite can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawed as sprite */
class CC_3D_DLL Sprite3D : public Node, public BlendProtocol
{
public:
    /** creates a Sprite3D*/
    static Sprite3D* create(const std::string &modelPath);

    // creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    
    /**set texture, set the first if multiple textures exist*/
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);
    
    /**get SubMeshState by index*/
    SubMeshState* getSubMeshState(int index) const;

    /**get mesh*/
    Mesh* getMesh() const { return _mesh; }
    
    /**get skin*/
    MeshSkin* getSkin() const { return _skin; }
    
    /**get AttachNode by bone name, return nullptr if not exist*/
    AttachNode* getAttachNode(const std::string& boneName);
    
    /**remove attach node*/
    void removeAttachNode(const std::string& boneName);
    
    /**remove all attach nodes*/
    void removeAllAttachNode();

    // overrides
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;
    
    /*
     * Get AABB
     * If the sprite has animation, it can't be calculated accuratly,
     * because bone can drive the vertices, we just use the origin vertices
     * to calculate the AABB.
     */
    AABB getAABB() const;
    
    /**
     * Returns 2d bounding-box
     * Note: the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
     */
    virtual Rect getBoundingBox() const override;

    // set which face is going to cull, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK, default GL_BACK
    void setCullFace(GLenum cullFace);
    // set cull face enable or not
    void setCullFaceEnabled(bool enable);

CC_CONSTRUCTOR_ACCESS:
    
    Sprite3D();
    virtual ~Sprite3D();
    bool initWithFile(const std::string &path);
    
    /**load sprite3d from cache, return true if succeed, false otherwise*/
    bool loadFromCache(const std::string& path);
    
    /**.mtl file should at the same directory with the same name if exist*/
    bool loadFromObj(const std::string& path);
    
    /**load from .c3b or .c3t*/
    bool loadFromC3x(const std::string& path);

    /**draw*/
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    /**get default shader*/
    virtual GLProgram* getDefaultGLProgram(bool textured = true);
    
    /**generate default GLProgramState*/
    void genGLProgramState();
    
    /**generate materials, and add them to cache, keyprefix is used as key prefix when added to cache*/
    void genMaterials(const std::string& keyprefix, const std::vector<std::string>& texpaths);

protected:
    Mesh*                        _mesh;//mesh
    MeshSkin*                    _skin;//skin
    Skeleton3D*                  _skeleton; //skeleton
    
    std::vector<MeshCommand>     _meshCommands; //render command each for one submesh
    
    Vector<SubMeshState*>        _subMeshStates; // SubMeshStates
    
    std::unordered_map<std::string, AttachNode*> _attachments;

    BlendFunc                    _blend;
    
    mutable AABB                 _aabb;                 // cache current aabb
    mutable Mat4                 _nodeToWorldTransform; // cache the matrix
};

extern std::string CC_3D_DLL s_attributeNames[];//attribute names array

NS_CC_END
#endif // __SPRITE3D_H_
