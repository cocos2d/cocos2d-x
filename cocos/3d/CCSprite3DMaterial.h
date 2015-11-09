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

#ifndef __CCSPRIT3DMATERIAL_H__
#define __CCSPRIT3DMATERIAL_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"
#include "renderer/CCMaterial.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class Texture2D;

/** @class Sprite3DMaterial
 *  @brief @~english Sprite3DMaterial: Material for Sprite3D.
	@~chinese 3D精灵使用的材质
    @js NA
    @lua NA
 */
class CC_DLL Sprite3DMaterial : public Material
{
public:
    /** @~english Material type, there are mainly two types of materials. Built in materials and Custom material
        @~chinese 材质类型。主要包含2种材质：内置材质和用自定义材质
    */
    enum class MaterialType
    {
        /** @~english Built in material
            @~chinese 内置材质
        */
        UNLIT, /**@~english unlit material.  @~chinese 无光照材质 */
        UNLIT_NOTEX, /**@~english unlit material without texture.  @~chinese 无光照无纹理材质 */
        VERTEX_LIT, /**@~english vertex lit.  @~chinese 定点光照 */
        DIFFUSE, /**@~english diffuse (pixel lighting).  @~chinese 散射光（像素光照） */
        DIFFUSE_NOTEX, /**@~english diffuse (without texture).  @~chinese 散射光（无纹理） */
        BUMPED_DIFFUSE, /**@~english bumped diffuse.  @~chinese 凹凸漫反射 */
        
        /** @~english Custom material
            @~chinese 自定义材质
        */
        CUSTOM, /**@~english Create from material file.  @~chinese 从材质文件创建 */
    };

    /** @~english Get material type
        @~chinese 获取材质类型
        @return @~english Material type @~chinese 材质类型
    */
    MaterialType getMaterialType() const { return _type; }

    /** @~english Create built in material from material type
        @~chinese 根据指定材质类型创建内置材质
        @param type @~english  Material type @~chinese 材质类型
        @param skinned @~english  Has skin? @~chinese 是否有皮肤
        @return @~english Created material @~chinese 创建的材质
    */
    static Sprite3DMaterial* createBuiltInMaterial(MaterialType type, bool skinned);

    /** @~english Create material with file name, it creates material from cache if it is previously loaded
        @~chinese 通过给定文件创建材质，如果材质已经被加载过则返回缓存中的材质
        @param path @~english  Path of material file @~chinese 材质文件路径
        @return @~english Created material @~chinese 创建的材质
    */
    static Sprite3DMaterial* createWithFilename(const std::string& path);

    /** @~english Create material with GLProgramState
        @~chinese 使用GLProgramState创建材质
        @param programState @~english  GLProgramState instance @~chinese GLProgramState实例
        @return @~english Created material @~chinese 创建的材质
    */
    static Sprite3DMaterial* createWithGLStateProgram(GLProgramState* programState);

    /** @~english Create all build in materials
        @~chinese 创建全部内置材质
    */
    static void createBuiltInMaterial();

    /** @~english Release all built in materials
        @~chinese 释放全部内置材质
    */
    static void releaseBuiltInMaterial();

    /** @~english Release all cached materials
        @~chinese 释放全部缓存的材质
    */
    static void releaseCachedMaterial();

    /** @~english Clone material
        @~chinese 克隆材质
    */
    virtual Material* clone() const override;
    
protected:
    
    MaterialType _type;
    static std::unordered_map<std::string, Sprite3DMaterial*> _materials; //cached material
    static Sprite3DMaterial* _unLitMaterial;
    static Sprite3DMaterial* _unLitNoTexMaterial;
    static Sprite3DMaterial* _vertexLitMaterial;
    static Sprite3DMaterial* _diffuseMaterial;
    static Sprite3DMaterial* _diffuseNoTexMaterial;
    static Sprite3DMaterial* _bumpedDiffuseMaterial;
    
    static Sprite3DMaterial* _unLitMaterialSkin;
    static Sprite3DMaterial* _vertexLitMaterialSkin;
    static Sprite3DMaterial* _diffuseMaterialSkin;
    static Sprite3DMaterial* _bumpedDiffuseMaterialSkin;
};

/** @class Sprite3DMaterialCache
    @brief @~english the sprite3D material is only texture for now
	@~chinese 当前的材质仅仅使用了纹理
    @js NA
    @lua NA
*/
class Sprite3DMaterialCache
{
public:
    /** @~english get & destroy cache
        @~chinese 得到此对象的实例
        @return @~english the instance of this object @~chinese 此对象的实例
    */
    static Sprite3DMaterialCache* getInstance();

    /** @~english destroy the instance
        @~chinese 销毁实例
    */
    static void destroyInstance();

    /** @~english add to cache
        @~chinese 添加到缓存中
        @param key @~english  the key of material @~chinese 材质的键
        @param tex @~english  the Texture2D to add @~chinese 添加的Texture2D
        @return @~english Whether or not the operation is successful @~chinese 是否成功
    */
    bool addSprite3DMaterial(const std::string& key, Texture2D* tex);

    /** @~english get material from cache
        @~chinese 从缓存中获得材质
        @param key @~english  the key of material @~chinese 材质的键
        @return @~english the Texture2D of the given material @~chinese 给定材质的Texture2D
    */
    Texture2D* getSprite3DMaterial(const std::string& key);

    /** @~english remove all spritematerial
        @~chinese 删除所有spritematerial
    */
    void removeAllSprite3DMaterial();

    /** @~english remove unused spritematerial
        @~chinese 删除未使用的spritematerial
    */
    void removeUnusedSprite3DMaterial();
    
CC_CONSTRUCTOR_ACCESS:
    
    Sprite3DMaterialCache();
    ~Sprite3DMaterialCache();
    
protected:
    static Sprite3DMaterialCache* _cacheInstance;//instance
    std::unordered_map<std::string, Texture2D*> _materials; //cached material
    
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSPRIT3DMATERIAL_H__
