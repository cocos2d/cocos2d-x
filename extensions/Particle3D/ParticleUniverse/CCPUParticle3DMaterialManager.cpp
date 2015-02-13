/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptCompiler.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DTranslateManager.h"
#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID/* || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX*/)
//#include <sys/io.h>
//#include <sys/dir.h>
//#include <sys/types.h>
#include "android/CCFileUtils-android.h"
#include <android/asset_manager.h>
//#include <sys/stat.h>
//#include <dirent.h>
//#include <unistd.h>
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
        iter->release();
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
        if (iter->name == name)
            return iter;
    }
    return nullptr;
}

bool PUParticle3DMaterialCache::loadMaterials( const std::string &file )
{
    //std::string data = FileUtils::getInstance()->getStringFromFile(file);
    //auto iter = _materialMap.find(file);
    //if (iter != _materialMap.end()) return true;
    bool isFirstCompile = true;
    auto list = PUScriptCompiler::Instance()->compile(file, isFirstCompile);
    if (list == nullptr || list->empty()) return false;
    if (isFirstCompile){
        PUParticle3DTranslateManager::Instance()->translateMaterialSystem(this, list);
    }
    return true;
}

void PUParticle3DMaterialCache::addMaterial( PUParticle3DMaterial *material )
{
    for (auto iter : _materialMap){
        if (iter->name == material->name){
          CCLOG("warning: Material has existed (FilePath: %s,  MaterialName: %s)", material->fileName.c_str(), material->name.c_str());
        return;
      }
    }

    material->retain();
    _materialMap.push_back(material);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
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
#endif

bool PUParticle3DMaterialCache::loadMaterialsFromSearchPaths( const std::string &fileFolder )
{
    bool state = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    //for (auto iter : FileUtils::getInstance()->getSearchPaths()){
        std::string seg("/");
        std::string fullPath = fileFolder + seg + std::string("*.material");
        _finddata_t data;
        intptr_t handle = _findfirst(fullPath.c_str(), &data);
        int done = 0;
        while ((handle != -1) && (done == 0))
        {
            loadMaterials(fileFolder + seg + std::string(data.name));
            done = _findnext(handle, &data);
            state = true;
        }
        _findclose(handle);
   // }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID/* || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX*/)
    //TODO:
    //for (auto iter : FileUtils::getInstance()->getSearchPaths()){
        //std::string fullPath = fileFolder + std::string("*.material");
        //struct ffblk data;
        //int done = findfirst(fullPath.c_str(), &data, 512);
        //while (!done)
        //{
        //    loadMaterials(fileFolder + std::string(data.name));
        //    done = findnext(&data);
        //    state = true;
        //}
    //}

    //struct dirent* ent = NULL;
    //DIR* pDir;
    //pDir = opendir(fileFolder.c_str());
    //while(NULL != (ent = readdir(pDir)))
    //{
    //    //std::string fullpath = fileFolder + "/" + ent->d_name;
    //    //CCLOG("%s", fullpath.c_str());
    //    //if(8 == ent->d_type)  //在nfs或xfs下，有的文件d_type也是0
    //    //if(IsFile(fullpath))
    //    //{
    //    //    if(strstr(ent->d_name, "material")!=NULL)
    //    //    {
    //    //        loadMaterials(fullpath);
    //    //        //files.push_back(ent->d_name);
    //    //    }
    //    //}
    //}
    //closedir(pDir);

    //DIR *dp;
    //struct dirent *entry;
    //struct stat statbuf;
    //int count = 0;

    //dp=opendir(fileFolder.c_str());
    //chdir(fileFolder.c_str());
    //while((entry = readdir(dp)) != nullptr && count < 255)
    //{
    //    //++count;
    //    //stat(entry->d_name,&statbuf);
    //    //if(!S_ISREG(statbuf.st_mode))
    //    //    continue;

    //    //std::string fullpath = fileFolder + std::string(entry->d_name);
    //    //loadMaterials(fullpath);
    //    //CCLOG("%s",entry->d_name);
    //}
    //closedir(dp);
    std::string::size_type pos = fileFolder.find("assets/");
    std::string relativePath = fileFolder;
    if (pos != std::string::npos) {
        // "assets/" is at the beginning of the path and we don't want it
        relativePath = fileFolder.substr(pos + strlen("assets/"));
    }
    AAssetDir *dir = AAssetManager_openDir(FileUtilsAndroid::getAssetManager(), relativePath.c_str());
    const char *fileName = nullptr;
    std::string seg("/");
    while ((fileName = AAssetDir_getNextFileName(dir)) != nullptr)
    {
        std::string fullpath = fileFolder + seg + std::string(fileName);
        loadMaterials(fullpath);
    }
    AAssetDir_close(dir);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    ftw(fileFolder.c_str(), iterPath, 500);
#endif

    return state;
}

NS_CC_END