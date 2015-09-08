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
 * @addtogroup _3d
 * @{
 */

class Texture2D;

class CC_DLL Sprite3DMaterial : public Material
{
public:
    enum class MaterialType
    {
        UNLIT,
        UNLIT_NOTEX,
        VERTEX_LIT,
        DIFFUSE,
        DIFFUSE_NOTEX,
        BUMPED_DIFFUSE,
        
        CUSTOM,
    };
    
    MaterialType getMaterialType() const { return _type; }
    
    static Sprite3DMaterial* createBuiltInMaterial(MaterialType type, bool skinned);
    
    static Sprite3DMaterial* createWithFilename(const std::string& path);
    
    static Sprite3DMaterial* createWithGLStateProgram(GLProgramState* programState);
    
    static void createBuiltInMaterial();
    
    static void releaseBuiltInMaterial();
    
    static void releaseCachedMaterial();
    
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
