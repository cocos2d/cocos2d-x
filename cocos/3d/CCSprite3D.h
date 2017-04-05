/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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

/**
 * @addtogroup _3d
 * @{
 */

class Mesh;
class Texture2D;
class MeshSkin;
class AttachNode;
struct NodeData;
/** @brief Sprite3D: A sprite can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawn as sprite */
class CC_DLL Sprite3D : public Node, public BlendProtocol
{
public:
    /**
     * Creates an empty sprite3D without 3D model and texture.
     *
     * @return An autoreleased sprite3D object.
     */
    static Sprite3D* create();
    
    /** creates a Sprite3D*/
    static Sprite3D* create(const std::string &modelPath);
  
    // creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    
    /** create 3d sprite asynchronously
     * If the 3d model was previously loaded, it will create a new 3d sprite and the callback will be called at once.
     * Otherwise it will load the model file in a new thread, and when the 3d sprite is loaded, the callback will be called with the created Sprite3D and a user-defined parameter.
     * The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
     * @param modelPath model to be loaded
     * @param callback callback after loading
     * @param callbackparam user defined parameter for the callback
     */
    static void createAsync(const std::string &modelPath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);
    
    static void createAsync(const std::string &modelPath, const std::string &texturePath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);
    
    /**set diffuse texture, set the first if multiple textures exist*/
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);
    
    /**get Mesh by index*/
    Mesh* getMeshByIndex(int index) const;
    
    /**get Mesh by Name, it returns the first one if there are more than one mesh with the same name */
    Mesh* getMeshByName(const std::string& name) const;
    
    /** 
     * get mesh array by name, returns all meshes with the given name
     *
     * @lua NA
     */
    std::vector<Mesh*> getMeshArrayByName(const std::string& name) const;

    /**get mesh*/
    Mesh* getMesh() const;
    
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
    /** just remember bind attributes */
    virtual void setGLProgram(GLProgram *glprogram) override;
    
    /*
     * Get AABB
     * If the sprite has animation, it can't be calculated accurately,
     * because bone can drive the vertices, we just use the origin vertices
     * to calculate the AABB.
     */
    const AABB& getAABB() const;
    
    /* 
     * Get AABB Recursively
     * Because some times we may have an empty Sprite3D Node as parent, but
     * the Sprite3D don't contain any meshes, so getAABB()
     * will return a wrong value at that time.
     */
    AABB getAABBRecursively();
    
    /**
     * Executes an action, and returns the action that is executed. For Sprite3D special logic are needed to take care of Fading.
     *
     * This node becomes the action's target. Refer to Action::getTarget()
     * @warning Actions don't retain their target.
     *
     * @return An Action pointer
     */
    virtual Action* runAction(Action* action) override;
    
    /**
     * Force to write to depth buffer, this is useful if you want to achieve effects like fading.
     */
    void setForceDepthWrite(bool value) { _forceDepthWrite = value; }
    bool isForceDepthWrite() const { return _forceDepthWrite;};
    
    /**
     * Returns 2d bounding-box
     * Note: the bounding-box is just get from the AABB which as Z=0, so that is not very accurate.
     */
    virtual Rect getBoundingBox() const override;

    // set which face is going to cull, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK, default GL_BACK
    void setCullFace(GLenum cullFace);
    // set cull face enable or not
    void setCullFaceEnabled(bool enable);
    
    /** light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff */
    void setLightMask(unsigned int mask) { _lightMask = mask; }
    unsigned int getLightMask() const { return _lightMask; }
    
    /**draw*/
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /** Adds a new material to the sprite.
     The Material will be applied to all the meshes that belong to the sprite.
     Internally it will call `setMaterial(material,-1)`
     */
    void setMaterial(Material* material);

    /** Adds a new material to a particular mesh of the sprite.
     meshIndex is the mesh that will be applied to.
     if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
     */
    void setMaterial(Material* material, int meshIndex);

    /** Adds a new material to a particular mesh of the sprite.
     meshIndex is the mesh that will be applied to.
     if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
     */
    Material* getMaterial(int meshIndex) const;
    
    /**
    * force set this Sprite3D to 2D render queue
    */
    void setForce2DQueue(bool force2D);

    /**
    * Get meshes used in sprite 3d
    */
    const Vector<Mesh*>& getMeshes() const { return _meshes; }

CC_CONSTRUCTOR_ACCESS:
    
    Sprite3D();
    virtual ~Sprite3D();
    
    virtual bool init() override;
    
    bool initWithFile(const std::string &path);
    
    bool initFrom(const NodeDatas& nodedatas, const MeshDatas& meshdatas, const MaterialDatas& materialdatas);
    
    /**load sprite3d from cache, return true if succeed, false otherwise*/
    bool loadFromCache(const std::string& path);
    
    /** load file and set it to meshedatas, nodedatas and materialdatas, obj file .mtl file should be at the same directory if exist */
    bool loadFromFile(const std::string& path, NodeDatas* nodedatas, MeshDatas* meshdatas,  MaterialDatas* materialdatas);

    /**
     * Visits this Sprite3D's children and draw them recursively.
     * Note: all its children will rendered as 3D objects
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
    
    /**generate default material*/
    void genMaterial(bool useLight = false);

    void createNode(NodeData* nodedata, Node* root, const MaterialDatas& materialdatas, bool singleSprite);
    void createAttachSprite3DNode(NodeData* nodedata, const MaterialDatas& materialdatas);
    Sprite3D* createSprite3DNode(NodeData* nodedata, ModelData* modeldata, const MaterialDatas& materialdatas);

    /**get MeshIndexData by Id*/
    MeshIndexData* getMeshIndexData(const std::string& indexId) const;
    
    void addMesh(Mesh* mesh);
    
    void onAABBDirty() { _aabbDirty = true; }
    
    void afterAsyncLoad(void* param);

    static AABB getAABBRecursivelyImp(Node *node);
    
protected:

    Skeleton3D*                  _skeleton; //skeleton
    
    Vector<MeshVertexData*>      _meshVertexDatas;
    
    std::unordered_map<std::string, AttachNode*> _attachments;

    BlendFunc                    _blend;
    
    Vector<Mesh*>              _meshes;

    mutable AABB                 _aabb;                 // cache current aabb
    mutable Mat4                 _nodeToWorldTransform; // cache the matrix
    mutable bool                 _aabbDirty;
    unsigned int                 _lightMask;
    bool                         _shaderUsingLight; // is current shader using light ?
    bool                         _forceDepthWrite; // Always write to depth buffer
    bool                         _usingAutogeneratedGLProgram;
    
    struct AsyncLoadParam
    {
        std::function<void(Sprite3D*, void*)> afterLoadCallback; // callback after load
        void*                           callbackParam;
        bool                            result; // sprite load result
        std::string                     modelPath;
        std::string                     texPath; //
        MeshDatas* meshdatas;
        MaterialDatas* materialdatas;
        NodeDatas*   nodeDatas;
    };
    AsyncLoadParam             _asyncLoadParam;
};

///////////////////////////////////////////////////////
/**
 * Sprite3DCache
 * @brief the cache data of Sprite3D, use to speed up Sprite3D::create
 */
class CC_DLL Sprite3DCache
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

    /**
     * get the SpriteData struct
     *
     * @lua NA
     */
    Sprite3DData* getSpriteData(const std::string& key) const;
    
    /**
     * add the SpriteData into Sprite3D by given the specified key
     *
     * @lua NA
     */
    bool addSprite3DData(const std::string& key, Sprite3DData* spritedata);
    
    /**remove the SpriteData from Sprite3D by given the specified key*/
    void removeSprite3DData(const std::string& key);
    
    /**remove all the SpriteData from Sprite3D*/
    void removeAllSprite3DData();
    
    CC_CONSTRUCTOR_ACCESS:
    Sprite3DCache();
    ~Sprite3DCache();
    
protected:
    
    
    static Sprite3DCache*                        _cacheInstance;
    std::unordered_map<std::string, Sprite3DData*> _spriteDatas; //cached sprite data
};

// end of 3d group
/// @}

NS_CC_END
#endif // __SPRITE3D_H_
