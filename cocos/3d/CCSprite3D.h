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

#include <unordered_map>

#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCGLProgramState.h"
#include "3d/CCSkeleton3D.h" // need to include for lua-binding
#include "3d/CCAABB.h"
#include "3d/CCBundle3DData.h"
#include "3d/CCMeshVertexIndexData.h"


NS_CC_BEGIN

class Mesh;
class Texture2D;
class MeshSkin;
class AttachNode;
struct NodeData;
/** Sprite3D: A sprite can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawed as sprite */
class CC_DLL Sprite3D : public Node, public BlendProtocol
{
public:
    /** creates a Sprite3D*/
    static Sprite3D* create(const std::string &modelPath);
  
    // creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    
    /**set texture, set the first if multiple textures exist*/
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);
    
    /**get Mesh by index*/
    Mesh* getMeshByIndex(int index) const;
    
    /**get Mesh by Name, it returns the first one if there are more than one mesh with the same name */
    Mesh* getMeshByName(const std::string& name) const;
    
    /** get mesh array by name, returns all meshes with the given name */
    std::vector<Mesh*> getMeshArrayByName(const std::string& name) const;

    /**get mesh*/
    Mesh* getMesh() const { return _meshes.at(0); }
    
    /** get mesh count */
    ssize_t getMeshCount() const { return _meshes.size(); }
    
    /**get skin*/
    CC_DEPRECATED_ATTRIBUTE MeshSkin* getSkin() const;
    
    Skeleton3D* getSkeleton() const { return _skeleton; }
    
    /**get AttachNode by bone name, return nullptr if not exist*/
    AttachNode* getAttachNode(const std::string& boneName);
    
    /**remove attach node*/
    void removeAttachNode(const std::string& boneName);
    
    /**remove all attach nodes*/
    void removeAllAttachNode();

    // overrides
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;
    
    // overrides
    /** set GLProgramState, you should bind attributes by yourself */
    virtual void setGLProgramState(GLProgramState *glProgramState) override;
    /** just rember bind attributes */
    virtual void setGLProgram(GLProgram *glprogram) override;
    
    /*
     * Get AABB
     * If the sprite has animation, it can't be calculated accuratly,
     * because bone can drive the vertices, we just use the origin vertices
     * to calculate the AABB.
     */
    const AABB& getAABB() const;
    
    /**
     * Returns 2d bounding-box
     * Note: the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
     */
    virtual Rect getBoundingBox() const override;

    // set which face is going to cull, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK, default GL_BACK
    void setCullFace(GLenum cullFace);
    // set cull face enable or not
    void setCullFaceEnabled(bool enable);
    
    /** light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff */
    void setLightMask(unsigned int mask) { _lightMask = mask; }
    unsigned int getLightMask() const { return _lightMask; }

CC_CONSTRUCTOR_ACCESS:
    
    Sprite3D();
    virtual ~Sprite3D();
    bool initWithFile(const std::string &path);
    
    bool initFrom(const NodeDatas& nodedatas, const MeshDatas& meshdatas, const MaterialDatas& materialdatas);
    
    /**load sprite3d from cache, return true if succeed, false otherwise*/
    bool loadFromCache(const std::string& path);
    
    /**.mtl file should at the same directory with the same name if exist*/
    bool loadFromObj(const std::string& path);
    
    /**load from .c3b or .c3t*/
    bool loadFromC3x(const std::string& path);

    /**draw*/
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    /**generate default GLProgramState*/
    void genGLProgramState(bool useLight = false);

    void createNode(NodeData* nodedata, Node* root, const MaterialDatas& matrialdatas, bool singleSprite);
    void createAttachSprite3DNode(NodeData* nodedata,const MaterialDatas& matrialdatas);
    Sprite3D* createSprite3DNode(NodeData* nodedata,ModelData* modeldata,const MaterialDatas& matrialdatas);

    /**get MeshIndexData by Id*/
    MeshIndexData* getMeshIndexData(const std::string& indexId) const;
    
    void  addMesh(Mesh* mesh);
    
    void onAABBDirty() { _aabbDirty = true; }
    
protected:

    Skeleton3D*                  _skeleton; //skeleton
    
    Vector<MeshVertexData*>      _meshVertexDatas;
    
    std::unordered_map<std::string, AttachNode*> _attachments;

    BlendFunc                    _blend;
    
    Vector<Mesh*>              _meshes;

    mutable AABB                 _aabb;                 // cache current aabb
    mutable Mat4                 _nodeToWorldTransform; // cache the matrix
    bool                         _aabbDirty;
    unsigned int                 _lightMask;
    bool                         _shaderUsingLight; // is current shader using light ?
};

///////////////////////////////////////////////////////
class Sprite3DCache
{
public:
    struct Sprite3DData
    {
        Vector<MeshVertexData*>   meshVertexDatas;
        Vector<GLProgramState*>   glProgramStates;
        NodeDatas*      nodedatas;
        MaterialDatas*  materialdatas;
        ~Sprite3DData()
        {
            if (nodedatas)
                delete nodedatas;
            if (materialdatas)
                delete materialdatas;
            meshVertexDatas.clear();
            glProgramStates.clear();
        }
    };
    
    /**get & destroy*/
    static Sprite3DCache* getInstance();
    static void destroyInstance();
    
    Sprite3DData* getSpriteData(const std::string& key) const;
    
    bool addSprite3DData(const std::string& key, Sprite3DData* spritedata);
    
    void removeSprite3DData(const std::string& key);
    
    void removeAllSprite3DData();
    
    CC_CONSTRUCTOR_ACCESS:
    Sprite3DCache();
    ~Sprite3DCache();
    
protected:
    
    
    static Sprite3DCache*                        _cacheInstance;
    std::unordered_map<std::string, Sprite3DData*> _spriteDatas; //cached sprite datas
};

extern std::string CC_DLL s_attributeNames[];//attribute names array

NS_CC_END
#endif // __SPRITE3D_H_
