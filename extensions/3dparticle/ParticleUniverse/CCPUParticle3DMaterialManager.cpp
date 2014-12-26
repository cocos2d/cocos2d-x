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

#include "CCPUParticle3DMaterialManager.h"
#include "3dparticle/ParticleUniverse/CCPUParticle3DScriptCompiler.h"
#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include <io.h>
#include <dir.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include <ftw.h>
#endif
NS_CC_BEGIN


PUParticle3DMaterial::PUParticle3DMaterial()
: isEnabledLight(true)
, ambientColor(Vec4::ONE)
, diffuseColor(Vec4::ONE)
, specularColor(Vec4::ZERO)
, emissiveColor(Vec4::ZERO)
, shininess(0.0f)
, depthTest(true)
, depthWrite(true)
, wrapMode(GL_CLAMP_TO_EDGE)
{
    blendFunc.src = GL_ONE;
    blendFunc.dst = GL_ZERO;
}

PUParticle3DMaterialCache::PUParticle3DMaterialCache()
{
}


PUParticle3DMaterialCache::~PUParticle3DMaterialCache()
{
    for (auto iter : _materialMap){
        for (auto mt : iter.second){
            mt->release();
        }
    }
    _materialMap.clear();
}

PUParticle3DMaterialCache* PUParticle3DMaterialCache::Instance()
{
    static PUParticle3DMaterialCache pmm;
    return &pmm;
}

PUParticle3DMaterial* PUParticle3DMaterialCache::getMaterial( const std::string &name )
{
    for (auto iter : _materialMap){
        for (auto mt : iter.second){
            if (mt->name == name)
                return mt;
        }
    }
    return nullptr;
}

bool PUParticle3DMaterialCache::loadMaterials( const std::string &file )
{
    std::string data = FileUtils::getInstance()->getStringFromFile(file);
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(file);
    auto iter = _materialMap.find(fullPath);
    if (iter != _materialMap.end()) return true;

    PUScriptCompiler sc;
    return sc.compile(data, fullPath);
}

void PUParticle3DMaterialCache::addMaterial( PUParticle3DMaterial *material )
{
    auto iter = _materialMap.find(material->fileName);
    if (iter != _materialMap.end()){
        for (auto mt : iter->second){
            if (mt->name == material->name){
                CCLOG("warning: Material has existed (FilePath: %s,  MaterialName: %s)", material->fileName.c_str(), material->name.c_str());
                return;
            }
        }
    }
    material->retain();
    _materialMap[material->fileName].push_back(material);
}

int iterPath(const char *fpath, const struct stat *sb, int typeflag)
{
    if(typeflag == FTW_F)
    {
        auto len = strlen(fpath);
        if (len > 9 && strcmp(".material", fpath + len - 9) == 0)
            PUParticle3DMaterialCache::Instance()->loadMaterials(fpath);
    }
    return 0;
}

bool PUParticle3DMaterialCache::loadMaterialsFromSearchPaths( const std::string &fileSpec )
{
    bool state = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    for (auto iter : FileUtils::getInstance()->getSearchPaths()){
        std::string fullPath = iter + fileSpec;
        _finddata_t data;
        intptr_t handle = _findfirst(fullPath.c_str(), &data);
        int done = 0;
        while ((handle != -1) && (done == 0))
        {
            loadMaterials(data.name);
            done = _findnext(handle, &data);
            state = true;
        }
        _findclose(handle);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    //TODO:
//      for (auto iter : FileUtils::getInstance()->getSearchPaths()){
//          std::string fullPath = iter + fileSpec;
//          struct ffblk data;
//          int done = findfirst(fullPath.c_str(), &data, 512);
//          while (!done)
//          {
//              loadMaterials(data.name);
//              done = findnext(&data);
//              state = true;
//          }
//      }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    for (auto iter : FileUtils::getInstance()->getSearchPaths())
    {
        std::string fullPath = iter + fileSpec;
        ftw(fullPath.c_str(), iterPath, 500);
    }
#endif

    return state;
}

NS_CC_END