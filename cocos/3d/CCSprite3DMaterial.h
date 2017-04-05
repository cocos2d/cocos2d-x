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

#ifndef __CCSPRIT3DMATERIAL_H__
#define __CCSPRIT3DMATERIAL_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"
#include "renderer/CCMaterial.h"
#include "3d/CCBundle3DData.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Texture2D;

/**
 * @brief Sprite3DMaterial: Material for Sprite3D.
 */
class CC_DLL Sprite3DMaterial : public Material
{
public:
    /**
     * Material type, there are mainly two types of materials. Built in materials and Custom material
     */
    enum class MaterialType
    {
        //Built in material
        UNLIT, //unlit material
        UNLIT_NOTEX, //unlit material without texture
        VERTEX_LIT, // vertex lit
        DIFFUSE, // diffuse (pixel lighting)
        DIFFUSE_NOTEX, //diffuse (without texture)
        BUMPED_DIFFUSE, //bumped diffuse
        
        //Custom material
        CUSTOM, //Create from material file
    };
    
    /**
     * Get material type
     * @return Material type
     */
    MaterialType getMaterialType() const { return _type; }
    
    /**
     * Create built in material from material type
     * @param type Material type
     * @param skinned Has skin?
     * @return Created material
     */
    static Sprite3DMaterial* createBuiltInMaterial(MaterialType type, bool skinned);
    
    /**
     * Create material with file name, it creates material from cache if it is previously loaded
     * @param path Path of material file
     * @return Created material
     */
    static Sprite3DMaterial* createWithFilename(const std::string& path);
    
    /**
     * Create material with GLProgramState
     * @param programState GLProgramState instance
     * @return Created material
     */
    static Sprite3DMaterial* createWithGLStateProgram(GLProgramState* programState);
    
    void setTexture(Texture2D* tex, NTextureData::Usage usage);
    
    /**
     * Create all build in materials
     */
    static void createBuiltInMaterial();
    
    /**
     * Release all built in materials
     */
    static void releaseBuiltInMaterial();
    
    /**
     * Release all cached materials
     */
    static void releaseCachedMaterial();
    
    /**
     * Clone material
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

/**
 * @brief the sprite3D material is only texture for now
 * @js NA
 * @lua NA
 */
class Sprite3DMaterialCache
{
public:
    /**get & destroy cache*/
    static Sprite3DMaterialCache* getInstance();

    /**destroy the instance*/
    static void destroyInstance();
    
    /**add to cache*/
    bool addSprite3DMaterial(const std::string& key, Texture2D* tex);
    
    /**get material from cache*/
    Texture2D* getSprite3DMaterial(const std::string& key);
    
    /**remove all spritematerial*/
    void removeAllSprite3DMaterial();
    /**remove unused spritematerial*/
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
