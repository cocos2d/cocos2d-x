/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/CCFileUtils-android.h"
#include "platform/CCCommon.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#include "base/ZipUtils.h"

#include <stdlib.h>
#include <sys/stat.h>

#define  LOG_TAG    "CCFileUtils-android.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  ASSETS_FOLDER_NAME          "assets/"
#define  ASSETS_FOLDER_NAME_LENGTH   7

using namespace std;

#define DECLARE_GUARD std::lock_guard<std::recursive_mutex> mutexGuard(_mutex)

NS_CC_BEGIN

AAssetManager* FileUtilsAndroid::assetmanager = nullptr;
ZipFile* FileUtilsAndroid::obbfile = nullptr;

void FileUtilsAndroid::setassetmanager(AAssetManager* a) {
    if (nullptr == a) {
        LOGD("setassetmanager : received unexpected nullptr parameter");
        return;
    }

    cocos2d::FileUtilsAndroid::assetmanager = a;
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsAndroid();
        if (!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsAndroid");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsAndroid::FileUtilsAndroid()
{
}

FileUtilsAndroid::~FileUtilsAndroid()
{
    if (obbfile)
    {
        delete obbfile;
        obbfile = nullptr;
    }
}

bool FileUtilsAndroid::init()
{
    DECLARE_GUARD;

    _defaultResRootPath = ASSETS_FOLDER_NAME;
    
    std::string assetsPath(getApkPath());
    if (assetsPath.find("/obb/") != std::string::npos)
    {
        obbfile = new ZipFile(assetsPath);
    }

    return FileUtils::init();
}

std::string FileUtilsAndroid::getNewFilename(const std::string &filename) const
{
    std::string newFileName = FileUtils::getNewFilename(filename);
    // ../xxx do not fix this path
    auto pos = newFileName.find("../");
    if (pos == std::string::npos || pos == 0)
    {
        return newFileName;
    }

    std::vector<std::string> v(3);
    v.resize(0);
    auto change = false;
    size_t size = newFileName.size();
    size_t idx = 0;
    bool noexit = true;
    while (noexit)
    {
        pos = newFileName.find('/', idx);
        std::string tmp;
        if (pos == std::string::npos)
        {
            tmp = newFileName.substr(idx, size - idx);
            noexit = false;
        }else
        {
            tmp = newFileName.substr(idx, pos - idx + 1);
        }
        auto t = v.size();
        if (t > 0 && v[t-1].compare("../") != 0 &&
             (tmp.compare("../") == 0 || tmp.compare("..") == 0))
        {
            v.pop_back();
            change = true;
        }else
        {
            v.push_back(tmp);
        }
        idx = pos + 1;
    }

    if (change)
    {
        newFileName.clear();
        for (auto &s : v)
        {
            newFileName.append(s);
        }
    }
    return newFileName;
}

bool FileUtilsAndroid::isFileExistInternal(const std::string& strFilePath) const
{
    
    DECLARE_GUARD;

    if (strFilePath.empty())
    {
        return false;
    }

    bool bFound = false;

    // Check whether file exists in apk.
    if (strFilePath[0] != '/')
    {
        const char* s = strFilePath.c_str();

        // Found "assets/" at the beginning of the path and we don't want it
        if (strFilePath.find(_defaultResRootPath) == 0) s += _defaultResRootPath.length();
        
        if (obbfile && obbfile->fileExists(s))
        {
            bFound = true;
        }
        else if (FileUtilsAndroid::assetmanager)
        {
            AAsset* aa = AAssetManager_open(FileUtilsAndroid::assetmanager, s, AASSET_MODE_UNKNOWN);
            if (aa)
            {
                bFound = true;
                AAsset_close(aa);
            } else {
                // CCLOG("[AssetManager] ... in APK %s, found = false!", strFilePath.c_str());
            }
        }
    }
    else
    {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if (fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool FileUtilsAndroid::isDirectoryExistInternal(const std::string& dirPath) const
{
    if (dirPath.empty())
    {
        return false;
    }

    std::string dirPathCopy = dirPath;
    if(dirPathCopy[dirPathCopy.length() - 1] == '/')
    {
        dirPathCopy.erase(dirPathCopy.length() - 1);
    }

    const char* s = dirPathCopy.c_str();
    
    // find absolute path in flash memory
    if (s[0] == '/')
    {
        //CCLOG("find in flash memory dirPath(%s)", s);
        struct stat st;
        if (stat(s, &st) == 0)
        {
            return S_ISDIR(st.st_mode);
        }
    }
    else
    {


        // find it in apk's assets dir
        // Found "assets/" at the beginning of the path and we don't want it
        //CCLOG("find in apk dirPath(%s)", s);
        if (dirPath.find(ASSETS_FOLDER_NAME) == 0)
        {
            s += ASSETS_FOLDER_NAME_LENGTH;
        }

        if (FileUtilsAndroid::assetmanager)
        {
            AAssetDir* aa = AAssetManager_openDir(FileUtilsAndroid::assetmanager, s);
            if (aa && AAssetDir_getNextFileName(aa))
            {
                AAssetDir_close(aa);
                return true;
            }
        }
    }
    
    return false;
}

bool FileUtilsAndroid::isAbsolutePath(const std::string& strPath) const
{
    DECLARE_GUARD;
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/' || strPath.find(_defaultResRootPath) == 0)
    {
        return true;
    }
    return false;
}

long FileUtilsAndroid::getFileSize(const std::string& filepath) const
{
    DECLARE_GUARD;
    long size = FileUtils::getFileSize(filepath);
    if (size != -1) {
        return size;
    }
    
    if (FileUtilsAndroid::assetmanager)
    {
        string relativePath = filepath;
        if (filepath.find(_defaultResRootPath) == 0)
        {
            relativePath = filepath.substr(_defaultResRootPath.size());
        }
        
        AAsset* asset = AAssetManager_open(FileUtilsAndroid::assetmanager, relativePath.data(), AASSET_MODE_UNKNOWN);
        if (asset)
        {
            size = AAsset_getLength(asset);
            AAsset_close(asset);
        }
    }
    
    return size;
}

std::vector<std::string> FileUtilsAndroid::listFiles(const std::string& dirPath) const
{

    if(isAbsolutePath(dirPath)) return FileUtils::listFiles(dirPath);

    std::vector<std::string> fileList;
    string fullPath = fullPathForDirectory(dirPath);

    static const std::string apkprefix("assets/");
    string relativePath = "";
    size_t position = fullPath.find(apkprefix);
    if (0 == position) {
        // "assets/" is at the beginning of the path and we don't want it
        relativePath += fullPath.substr(apkprefix.size());
    } else {
        relativePath = fullPath;
    }

    if(obbfile) return obbfile->listFiles(relativePath);

    if (nullptr == assetmanager) {
        LOGD("... FileUtilsAndroid::assetmanager is nullptr");
        return fileList;
    }

    if(relativePath[relativePath.length() - 1] == '/')
    {
        relativePath.erase(relativePath.length() - 1);
    }

    auto *dir = AAssetManager_openDir(assetmanager, relativePath.c_str());
    if(nullptr == dir) {
        LOGD("... FileUtilsAndroid::failed to open dir %s", relativePath.c_str());
        AAssetDir_close(dir);
        return fileList;
    }
    const char *tmpDir = nullptr;
    while((tmpDir = AAssetDir_getNextFileName(dir))!= nullptr)
    {
        string filepath(tmpDir);
        if(isDirectoryExistInternal(filepath)) filepath += "/";
        fileList.push_back(filepath);
    }
    AAssetDir_close(dir);
    return fileList;
}

FileUtils::Status FileUtilsAndroid::getContents(const std::string& filename, ResizableBuffer* buffer) const
{
    EngineDataManager::onBeforeReadFile();

    static const std::string apkprefix("assets/");
    if (filename.empty())
        return FileUtils::Status::NotExists;

    string fullPath = fullPathForFilename(filename);

    if (fullPath[0] == '/')
        return FileUtils::getContents(fullPath, buffer);

    string relativePath = string();
    size_t position = fullPath.find(apkprefix);
    if (0 == position) {
        // "assets/" is at the beginning of the path and we don't want it
        relativePath += fullPath.substr(apkprefix.size());
    } else {
        relativePath = fullPath;
    }
    
    if (obbfile)
    {
        if (obbfile->getFileData(relativePath, buffer))
            return FileUtils::Status::OK;
    }

    if (nullptr == assetmanager) {
        LOGD("... FileUtilsAndroid::assetmanager is nullptr");
        return FileUtils::Status::NotInitialized;
    }

    AAsset* asset = AAssetManager_open(assetmanager, relativePath.data(), AASSET_MODE_UNKNOWN);
    if (nullptr == asset) {
        LOGD("asset is nullptr");
        return FileUtils::Status::OpenFailed;
    }

    auto size = AAsset_getLength(asset);
    buffer->resize(size);

    int readsize = AAsset_read(asset, buffer->buffer(), size);
    AAsset_close(asset);

    if (readsize < size) {
        if (readsize >= 0)
            buffer->resize(readsize);
        return FileUtils::Status::ReadFailed;
    }

    return FileUtils::Status::OK;
}

string FileUtilsAndroid::getWritablePath() const
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = JniHelper::callStaticStringMethod("org.cocos2dx.lib.Cocos2dxHelper", "getCocos2dxWritablePath");

    if (tmp.length() > 0)
    {
        dir.append(tmp).append("/");

        return dir;
    }
    else
    {
        return "";
    }
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
