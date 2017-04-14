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

#include "3d/CCSprite3DMaterial.h"
#include "3d/CCMesh.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramStateCache.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"

NS_CC_BEGIN

Sprite3DMaterialCache* Sprite3DMaterialCache::_cacheInstance = nullptr;

std::unordered_map<std::string, Sprite3DMaterial*> Sprite3DMaterial::_materials;
Sprite3DMaterial* Sprite3DMaterial::_unLitMaterial = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_unLitNoTexMaterial = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_vertexLitMaterial = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_diffuseMaterial = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_diffuseNoTexMaterial = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_bumpedDiffuseMaterial = nullptr;

Sprite3DMaterial* Sprite3DMaterial::_unLitMaterialSkin = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_vertexLitMaterialSkin = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_diffuseMaterialSkin = nullptr;
Sprite3DMaterial* Sprite3DMaterial::_bumpedDiffuseMaterialSkin = nullptr;

void Sprite3DMaterial::createBuiltInMaterial()
{
    releaseBuiltInMaterial();
    
    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_TEXTURE);
    auto glprogramstate = GLProgramState::create(glProgram);
    _unLitMaterialSkin = new (std::nothrow) Sprite3DMaterial();
    if (_unLitMaterialSkin && _unLitMaterialSkin->initWithGLProgramState(glprogramstate))
    {
        _unLitMaterialSkin->_type = Sprite3DMaterial::MaterialType::UNLIT;
    }
    
    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE);
    glprogramstate = GLProgramState::create(glProgram);
    _diffuseMaterialSkin = new (std::nothrow) Sprite3DMaterial();
    if (_diffuseMaterialSkin && _diffuseMaterialSkin->initWithGLProgramState(glprogramstate))
    {
        _diffuseMaterialSkin->_type = Sprite3DMaterial::MaterialType::DIFFUSE;
    }
    
    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE);
    glprogramstate = GLProgramState::create(glProgram);
    _diffuseMaterial = new (std::nothrow) Sprite3DMaterial();
    if (_diffuseMaterial && _diffuseMaterial->initWithGLProgramState(glprogramstate))
    {
        _diffuseMaterial->_type = Sprite3DMaterial::MaterialType::DIFFUSE;
    }
    
    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
    glprogramstate = GLProgramState::create(glProgram);
    _unLitMaterial = new (std::nothrow) Sprite3DMaterial();
    if (_unLitMaterial && _unLitMaterial->initWithGLProgramState(glprogramstate))
    {
        _unLitMaterial->_type = Sprite3DMaterial::MaterialType::UNLIT;
    }
    
    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION);
    glprogramstate = GLProgramState::create(glProgram);
    _unLitNoTexMaterial = new (std::nothrow) Sprite3DMaterial();
    if (_unLitNoTexMaterial && _unLitNoTexMaterial->initWithGLProgramState(glprogramstate))
    {
        _unLitNoTexMaterial->_type = Sprite3DMaterial::MaterialType::UNLIT_NOTEX;
    }
    
    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL);
    glprogramstate = GLProgramState::create(glProgram);
    _diffuseNoTexMaterial = new (std::nothrow) Sprite3DMaterial();
    if (_diffuseNoTexMaterial && _diffuseNoTexMaterial->initWithGLProgramState(glprogramstate))
    {
        _diffuseNoTexMaterial->_type = Sprite3DMaterial::MaterialType::DIFFUSE_NOTEX;
    }

    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE);
    glprogramstate = GLProgramState::create(glProgram);
    _bumpedDiffuseMaterial = new (std::nothrow) Sprite3DMaterial();
    if (_bumpedDiffuseMaterial && _bumpedDiffuseMaterial->initWithGLProgramState(glprogramstate))
    {
        _bumpedDiffuseMaterial->_type = Sprite3DMaterial::MaterialType::BUMPED_DIFFUSE;
    }

    glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE);
    glprogramstate = GLProgramState::create(glProgram);
    _bumpedDiffuseMaterialSkin = new (std::nothrow) Sprite3DMaterial();
    if (_bumpedDiffuseMaterialSkin && _bumpedDiffuseMaterialSkin->initWithGLProgramState(glprogramstate))
    {
        _bumpedDiffuseMaterialSkin->_type = Sprite3DMaterial::MaterialType::BUMPED_DIFFUSE;
    }
}

void Sprite3DMaterial::releaseBuiltInMaterial()
{
    CC_SAFE_RELEASE_NULL(_unLitMaterial);
    CC_SAFE_RELEASE_NULL(_unLitMaterialSkin);
    
    CC_SAFE_RELEASE_NULL(_unLitNoTexMaterial);
    CC_SAFE_RELEASE_NULL(_vertexLitMaterial);
    CC_SAFE_RELEASE_NULL(_diffuseMaterial);
    CC_SAFE_RELEASE_NULL(_diffuseNoTexMaterial);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterial);
    
    CC_SAFE_RELEASE_NULL(_vertexLitMaterialSkin);
    CC_SAFE_RELEASE_NULL(_diffuseMaterialSkin);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterialSkin);
}

void Sprite3DMaterial::releaseCachedMaterial()
{
    for (auto& it : _materials) {
        if (it.second)
            it.second->release();
    }
    _materials.clear();
}

Material* Sprite3DMaterial::clone() const
{
    auto material = new (std::nothrow) Sprite3DMaterial();
    if (material)
    {
        RenderState::cloneInto(material);
        
        for (const auto& technique: _techniques)
        {
            auto t = technique->clone();
            t->setParent(material);
            for (ssize_t i = 0; i < t->getPassCount(); i++) {
                t->getPassByIndex(i)->setParent(t);
            }
            material->_techniques.pushBack(t);
        }
        
        // current technique
        auto name = _currentTechnique->getName();
        material->_currentTechnique = material->getTechniqueByName(name);
        material->_type = _type;
        material->autorelease();
    }
    return material;
}

Sprite3DMaterial* Sprite3DMaterial::createBuiltInMaterial(MaterialType type, bool skinned)
{
    /////
    if (_diffuseMaterial == nullptr)
        createBuiltInMaterial();
    
    Sprite3DMaterial* material = nullptr;
    switch (type) {
        case Sprite3DMaterial::MaterialType::UNLIT:
            material = skinned ? _unLitMaterialSkin : _unLitMaterial;
            break;
            
        case Sprite3DMaterial::MaterialType::UNLIT_NOTEX:
            material = _unLitNoTexMaterial;
            break;
            
        case Sprite3DMaterial::MaterialType::VERTEX_LIT:
            CCASSERT(0, "not implement");
            break;
            
        case Sprite3DMaterial::MaterialType::DIFFUSE:
            material = skinned ? _diffuseMaterialSkin : _diffuseMaterial;
            break;
            
        case Sprite3DMaterial::MaterialType::DIFFUSE_NOTEX:
            material = _diffuseNoTexMaterial;
            break;
            
        case Sprite3DMaterial::MaterialType::BUMPED_DIFFUSE:
            material = skinned ? _bumpedDiffuseMaterialSkin : _bumpedDiffuseMaterial;
            break;
            
        default:
            break;
    }
    if (material)
        return (Sprite3DMaterial*)material->clone();
    
    return nullptr;
}

Sprite3DMaterial* Sprite3DMaterial::createWithFilename(const std::string& path)
{
    auto validfilename = FileUtils::getInstance()->fullPathForFilename(path);
    if (validfilename.size() > 0) {
        auto it = _materials.find(validfilename);
        if (it != _materials.end())
            return (Sprite3DMaterial*)it->second->clone();
        
        auto material = new (std::nothrow) Sprite3DMaterial();
        if (material->initWithFile(path))
        {
            material->_type = Sprite3DMaterial::MaterialType::CUSTOM;
            _materials[validfilename] = material;
            
            return (Sprite3DMaterial*)material->clone();
        }
        CC_SAFE_DELETE(material);
    }
    return nullptr;
}

Sprite3DMaterial* Sprite3DMaterial::createWithGLStateProgram(GLProgramState* programState)
{
    CCASSERT(programState, "Invalid GL Program State");
    
    auto mat = new (std::nothrow) Sprite3DMaterial();
    if (mat && mat->initWithGLProgramState(programState))
    {
        mat->_type = Sprite3DMaterial::MaterialType::CUSTOM;
        mat->autorelease();
        return mat;
        
    }
    CC_SAFE_DELETE(mat);
    return nullptr;
}

void Sprite3DMaterial::setTexture(Texture2D* tex, NTextureData::Usage usage)
{
    const auto& passes = getTechnique()->getPasses();
    for (auto& pass : passes) {
        pass->getGLProgramState()->setUniformTexture(s_uniformSamplerName[(int)usage], tex);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Sprite3DMaterialCache::Sprite3DMaterialCache()
{
    
}

Sprite3DMaterialCache::~Sprite3DMaterialCache()
{
    removeAllSprite3DMaterial();
}

Sprite3DMaterialCache* Sprite3DMaterialCache::getInstance()
{
    if (! _cacheInstance)
    {
        _cacheInstance = new (std::nothrow) Sprite3DMaterialCache();
    }
    
    return _cacheInstance;
}

void Sprite3DMaterialCache::destroyInstance()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

bool Sprite3DMaterialCache::addSprite3DMaterial(const std::string& key, Texture2D* texture)
{
    auto itr = _materials.find(key);
    if (itr == _materials.end())
    {
        CC_SAFE_RETAIN(texture);
        _materials[key] = texture;
        return true;
    }
    return false;
}

Texture2D* Sprite3DMaterialCache::getSprite3DMaterial(const std::string& key)
{
    auto itr = _materials.find(key);
    if (itr != _materials.end())
    {
        return itr->second;
    }
    return nullptr;
}

void Sprite3DMaterialCache::removeAllSprite3DMaterial()
{
    for (auto& itr : _materials) {
        CC_SAFE_RELEASE_NULL(itr.second);
    }
    _materials.clear();
}
void Sprite3DMaterialCache::removeUnusedSprite3DMaterial()
{
    for(auto it=_materials.cbegin(), itCend = _materials.cend(); it != itCend; /* nothing */) {
        auto value = it->second;
        if( value->getReferenceCount() == 1 ) {
            CCLOG("cocos2d: GLProgramStateCache: removing unused GLProgramState");
            
            value->release();
            it = _materials.erase(it);
        } else {
            ++it;
        }
    }
}

NS_CC_END
