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

/**
    @addtogroup _3d
    @{
*/

class Mesh;
class Texture2D;
class MeshSkin;
class AttachNode;
struct NodeData;

/** @class Sprite3D
    @brief @~english a sprite3D can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawed as sprite
    @~chinese 一个sprite3D可以从3D模型文件， OBJ， .c3t ， .c3b中被加载，然后就可以像精灵一样被绘制
*/
class CC_DLL Sprite3D : public Node, public BlendProtocol
{
public:
    /** @~english  Creates an empty sprite3D without 3D model and texture.
        @~chinese 创建一个空的Sprite3D没有3D模型和纹理。
        @return @~english an autoreleased sprite3D object. @~chinese 一个自动释放的Sprite3D对象。
    */
    static Sprite3D* create();

    /** @~english creates a Sprite3D
        @~chinese 创建一个Sprite3D
        @return @~english an autoreleased sprite3D object. @~chinese 一个自动释放的Sprite3D对象。
    */
    static Sprite3D* create(const std::string& modelPath);

    /** @~english creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
        @~chinese 创建一个Sprite3D。它只支持一个纹理，并重写内部纹理的texturepath”
        @return @~english an autoreleased sprite3D object. @~chinese 一个自动释放的Sprite3D对象。
    */
    static Sprite3D* create(const std::string& modelPath, const std::string& texturePath);

    /** @~english create 3d sprite asynchronously
        If the 3d model was previously loaded, it will create a new 3d sprite and the callback will be called at once.
        Otherwise it will load the model file in a new thread, and when the 3d sprite is loaded, the callback will be called with the created Sprite3D and a userdefined parameter.
        The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
        @~chinese 异步创建3D精灵
        如果三维模型已经被加载，它会立即创建一个新的3D精灵并且回调会被调用一次。
        否则会在一个新的线程加载模型文件，一旦加载完成，它会执行回调函数，并使用新创建的模型和自定义的用户数据做为参数。
        这个回调将在主线程调用，因此在回调函数中创建任何的cocos2d对象是安全的。
        @param modelPath @~english  model to be loaded @~chinese 被加载的模型
        @param callback @~english  callback after loading @~chinese 加载完成后的回调函数
        @param callbackparam @~english  user defined parameter for the callback @~chinese 用户定义的参数
    */
    static void createAsync(const std::string& modelPath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);

    static void createAsync(const std::string& modelPath, const std::string& texturePath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);

    /** @~english set texture, set the first if multiple textures exist
        @~chinese 设置纹理，只设置第一个，如果多重纹理的存在
    */
    void setTexture(const std::string& texFile);

    /** @~english set texture, set the first if multiple textures exist
        @~chinese 设置纹理，只设置第一个，如果多重纹理的存在
    */
    void setTexture(Texture2D* texture);

    /** @~english get Mesh by index
        @~chinese 通过索引得到网格
        @param index @~english  the specified index of a mesh @~chinese 一个索引用于指定网格
        @return @~english a mesh in the specified index @~chinese 指定的网格
    */
    Mesh* getMeshByIndex(int index) const;

    /** @~english get Mesh by Name, it returns the first one if there are more than one mesh with the same name
        @~chinese 通过名称得到网格，它返回第一个如果有多个具有相同名称的网格
        @param index @~english  the specified name of a mesh @~chinese 一个指定的名称
        @return @~english a mesh with the specified name @~chinese 具有指定名称的网格
    */
    Mesh* getMeshByName(const std::string& name) const;

    /** @~english get mesh array by name
        @~chinese 通过名称得到网格队列
        @param name @~english  the specified name of mesh @~chinese 指定的名称
        @return @~english all meshes with the given name @~chinese 与给定名称相符的所有的网格
        @lua NA
    */
    std::vector<Mesh*> getMeshArrayByName(const std::string& name) const;

    /** @~english get mesh
        @~chinese 得到网格
        @return @~english a mesh a index 0 @~chinese 网格索引0
    */
    Mesh* getMesh() const { return _meshes.at(0); }

    /** @return @~english mesh count @~chinese 得到网格的数量
    */
    ssize_t getMeshCount() const { return _meshes.size(); }

    /** @return @~english the skin @~chinese 得到皮肤
    */
    CC_DEPRECATED_ATTRIBUTE MeshSkin* getSkin() const;

    /** @return @~english the skeleton of sprite3d @~chinese 得到Sprite3D的骨架
    */
    Skeleton3D* getSkeleton() const { return _skeleton; }

    /** @~english get AttachNode by bone name
        @~chinese 得到attachnode通过骨骼的名字
        @param boneName @~english  the bone name @~chinese 骨骼的名字
        @return @~english AttachNode of the bone, nullptr if not exist @~chinese 如果骨骼不存在返回nullptr
    */
        AttachNode* getAttachNode(const std::string& boneName);

    /** @~english remove attach node of a bone
        @~chinese 删除骨骼所连接的attach node
        @param boneName @~english  the bone name @~chinese 骨的名字
    */
    void removeAttachNode(const std::string& boneName);

    /** @~english remove all attach nodes
        @~chinese 删除所有连接节点
    */
    void removeAllAttachNode();

    /** @~english set the blend methods for all meshes
        @~chinese 设置所有网格的混合方法
        @param blendFunc @~english  the new blendFunc object @~chinese 新blendfunc对象
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    /** @~english get the blend method
        @~chinese 得到混合的方法
        @return @~english the blendFunc object @~chinese blendfunc对象
    */
    virtual const BlendFunc& getBlendFunc() const override;

    // overrides
    /** @~english set GLProgramState, you should bind attributes by yourself
        @~chinese 设置glprogramstate，你应该自己绑定属性
        @param glProgramState @~english  the new GLProgramState to render with @~chinese 新的glprogramstate
    */
    virtual void setGLProgramState(GLProgramState* glProgramState) override;

    /** @~english set GLProgram, you should bind attributes by yourself
        @~chinese 设置glprogram，你应该自己绑定属性
        @param glprogram @~english  the new glprogram to render with @~chinese 新的glprogram
    */
    virtual void setGLProgram(GLProgram* glprogram) override;

    /** @~english Get AABB
        @~chinese 得到AABB
        @warning If the sprite has animation, it can't be calculated accuratly,
        because bone can drive the vertices, we just use the origin vertices
        to calculate the AABB.
        @return @~english the AABB object @~chinese AABB对象
    */
    const AABB& getAABB() const;

    /** @~english Get AABB Recursively,it will merge the aabb its own and all descendants
        @~chinese 递归得到AABB(递归的合并自身及其孩子的AABB)
        @warning Because some times we may have an empty Sprite3D Node as parent, but
        the Sprite3D don't contain any meshes, so getAABB()
        will return a wrong value at that time.
        @return @~english the AABB object @~chinese AABB对象
    */
    AABB getAABBRecursively();

    /** @~english  Executes an action, and returns the action that is executed. For Sprite3D special logic are needed to take care of Fading.
        This node becomes the action's target. Refer to Action::getTarget()
        @~chinese 执行一个action
        @warning Actions don't retain their target.
        @param action @~english  the action will be excuted @~chinese 将被执行的action
        @return @~english An Action pointer @~chinese 一个action的指针
    */
    virtual Action* runAction(Action* action) override;

    /** @~english  Force to write to depth buffer, this is useful if you want to achieve effects like fading.
        @~chinese 强制写入深度缓冲区，如果你想使用淡出效果，这样做也是有效的
        @param value @~english  the switching vale of method @~chinese 方法的切换阀
    */
    void setForceDepthWrite(bool value) { _forceDepthWrite = value; }

    /** @~english whether force to write to depth buffer
        @~chinese 是否强制写入深度缓冲区
        @return @~english the switching vale of method @~chinese 方法的切换阀
    */
    bool isForceDepthWrite() const { return _forceDepthWrite;};

    /** @~english  Returns 2d bounding-box
        @~chinese 返回二维包围盒
        @warning the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
        @return @~english the rect of boundingbox @~chinese 包围盒的矩形框
    */
    virtual Rect getBoundingBox() const override;

    /** @~english set which face is going to cull, default GL_BACK
        @~chinese 设置哪个面将要被剔除，默认gl_back
        @param cullFace @~english  which face is going to cull, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK @~chinese 哪个面将要被剔除，gl_back，gl_front，gl_front_and_back
    */
    void setCullFace(GLenum cullFace);

    /** @~english set cull face enable or not
        @~chinese 设置是否启用剔除
        @param enable @~english  the switching vale of method @~chinese 是否剔除
    */
    void setCullFaceEnabled(bool enable);

    /** @~english light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff
        @~chinese 设置灯光掩码
        @param mask @~english  the lightmask @~chinese 灯光掩码
    */
    void setLightMask(unsigned int mask) { _lightMask = mask; }

    /** @~english light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff
        @~chinese 返回灯光掩码
        @return @~english the lightmask @~chinese 灯光掩码
    */
    unsigned int getLightMask() const { return _lightMask; }

    /** @~english draw
        @~chinese 画
    */
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    /** @~english Adds a new material to the sprite.
        The Material will be applied to all the meshes that belong to the sprite.
        Internally it will call `setMaterial(material,-1)`
        @~chinese 给对象添加一个新的材质
        @param material @~english  the material to be applied @~chinese 材料被应用
    */
    void setMaterial(Material* material);

    /** @~english Adds a new material to a particular mesh of the sprite.
        meshIndex is the mesh that will be applied to.
        if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
        @~chinese 给对象的一个指定的网格添加材质
        @param material @~english  the material to be applied @~chinese 被添加的材质
        @param meshIndex @~english  the mesh index of whom want to apply the material @~chinese 添加材质的网格的索引
    */
    void setMaterial(Material* material, int meshIndex);

    /** @~english Get material of a particular mesh of the sprite.
        meshIndex is the mesh that will be applied to.
        if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
        @~chinese 对象的一个指定的网格的材质
        @param meshIndex @~english  the mesh index @~chinese 网格索引
        @return @~english the material of given mesh index @~chinese 指定风格的材质
    */
    Material* getMaterial(int meshIndex) const;

CC_CONSTRUCTOR_ACCESS:

    Sprite3D();
    virtual ~Sprite3D();

    virtual bool init() override;

    bool initWithFile(const std::string& path);

    bool initFrom(const NodeDatas& nodedatas, const MeshDatas& meshdatas, const MaterialDatas& materialdatas);

    /**load sprite3d from cache, return true if succeed, false otherwise*/
    bool loadFromCache(const std::string& path);

    /** load file and set it to meshedatas, nodedatas and materialdatas, obj file .mtl file should be at the same directory if exist */
    bool loadFromFile(const std::string& path, NodeDatas* nodedatas, MeshDatas* meshdatas,  MaterialDatas* materialdatas);

    /** Visits this Sprite3D's children and draw them recursively.
        Note: all its children will rendered as 3D objects
    */
    virtual void visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

    /**generate default GLProgramState*/
    void genGLProgramState(bool useLight = false);

    void createNode(NodeData* nodedata, Node* root, const MaterialDatas& matrialdatas, bool singleSprite);
    void createAttachSprite3DNode(NodeData* nodedata,const MaterialDatas& matrialdatas);
    Sprite3D* createSprite3DNode(NodeData* nodedata,ModelData* modeldata,const MaterialDatas& matrialdatas);

    /**get MeshIndexData by Id*/
    MeshIndexData* getMeshIndexData(const std::string& indexId) const;

    void addMesh(Mesh* mesh);

    void onAABBDirty() { _aabbDirty = true; }

    void afterAsyncLoad(void* param);

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
        std::string                     modlePath;
        std::string                     texPath; //
        MeshDatas* meshdatas;
        MaterialDatas* materialdatas;
        NodeDatas*   nodeDatas;
    };
    AsyncLoadParam             _asyncLoadParam;
};

///////////////////////////////////////////////////////
/** @class Sprite3DCache
    @brief @~english the cache data of Sprite3D, use to speed up Sprite3D::create
    @~chinese 一个缓存对象，用来加速Sprite3D的创建
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

    /** @~english get the instance of this object
        @~chinese 获得此对象的实例
        @return @~english the instance of this object @~chinese 此对象的实例
    */
    static Sprite3DCache* getInstance();

    /** @~english destroy the instance
        @~chinese 销毁实例
    */
    static void destroyInstance();

    /** @~english get the SpriteData struct
        @~chinese 得到spritedata结构
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata的key
        @return @~english the Sprite3DData @~chinese sprite3ddata对象
        @lua NA
    */
    Sprite3DData* getSpriteData(const std::string& key) const;

    /** @~english  add the SpriteData into Sprite3D by given the specified key
        @~chinese 添加spritedata到Sprite3D通过指定的关键字
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata的关键字
        @param spritedata @~english  the spritedata to add @~chinese 要添加的spritedata
        @return @~english Whether or not the operation is successful @~chinese 操作是否成功
        @lua NA
    */
    bool addSprite3DData(const std::string& key, Sprite3DData* spritedata);

    /** @~english remove the SpriteData from Sprite3D by given the specified key
        @~chinese 删除spritedata从Sprite3D通过指定键
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata的键
    */
    void removeSprite3DData(const std::string& key);

    /** @~english remove all the SpriteData from Sprite3D
        @~chinese 从Sprite3D删除所有spritedata
    */
    void removeAllSprite3DData();

CC_CONSTRUCTOR_ACCESS:
    Sprite3DCache();
    ~Sprite3DCache();

protected:

    static Sprite3DCache*                        _cacheInstance;
    std::unordered_map<std::string, Sprite3DData*> _spriteDatas; //cached sprite datas
};

// end of 3d group
/// @}

NS_CC_END
#endif // __SPRITE3D_H_
