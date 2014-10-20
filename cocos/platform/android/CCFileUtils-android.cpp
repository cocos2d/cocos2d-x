/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCFileUtils-android.h"
#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"

#include <stdlib.h>

#define  LOG_TAG    "CCFileUtils-android.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

NS_CC_BEGIN

AAssetManager* FileUtilsAndroid::assetmanager = nullptr;

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
        if(!s_sharedFileUtils->init())
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
}

bool FileUtilsAndroid::init()
{
    _defaultResRootPath = "assets/";
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
        if (strFilePath.find(_defaultResRootPath) == 0) s += strlen("assets/");

        if (FileUtilsAndroid::assetmanager) {
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
        if(fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool FileUtilsAndroid::isAbsolutePath(const std::string& strPath) const
{
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

Data FileUtilsAndroid::getData(const std::string& filename, bool forString)
{
    if (filename.empty())
    {
        return Data::Null;
    }
    
    unsigned char* data = nullptr;
    ssize_t size = 0;
    string fullPath = fullPathForFilename(filename);
    
    if (fullPath[0] != '/')
    {
        string relativePath = string();

        size_t position = fullPath.find("assets/");
        if (0 == position) {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath += fullPath.substr(strlen("assets/"));
        } else {
            relativePath += fullPath;
        }
        CCLOGINFO("relative path = %s", relativePath.c_str());

        if (nullptr == FileUtilsAndroid::assetmanager) {
            LOGD("... FileUtilsAndroid::assetmanager is nullptr");
            return Data::Null;
        }

        // read asset data
        AAsset* asset =
            AAssetManager_open(FileUtilsAndroid::assetmanager,
                               relativePath.c_str(),
                               AASSET_MODE_UNKNOWN);
        if (nullptr == asset) {
            LOGD("asset is nullptr");
            return Data::Null;
        }

        off_t fileSize = AAsset_getLength(asset);

        if (forString)
        {
            data = (unsigned char*) malloc(fileSize + 1);
            data[fileSize] = '\0';
        }
        else
        {
            data = (unsigned char*) malloc(fileSize);
        }

        int bytesread = AAsset_read(asset, (void*)data, fileSize);
        size = bytesread;

        AAsset_close(asset);
    }
    else
    {
        do
        {
            // read rrom other path than user set it
            //CCLOG("GETTING FILE ABSOLUTE DATA: %s", filename);
            const char* mode = nullptr;
            if (forString)
                mode = "rt";
            else
                mode = "rb";

            FILE *fp = fopen(fullPath.c_str(), mode);
            CC_BREAK_IF(!fp);
            
            long fileSize;
            fseek(fp,0,SEEK_END);
            fileSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            if (forString)
            {
                data = (unsigned char*) malloc(fileSize + 1);
                data[fileSize] = '\0';
            }
            else
            {
                data = (unsigned char*) malloc(fileSize);
            }
            fileSize = fread(data,sizeof(unsigned char), fileSize,fp);
            fclose(fp);
            
            size = fileSize;
        } while (0);
    }
    
    Data ret;
    if (data == nullptr || size == 0)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    else
    {
        ret.fastSet(data, size);
    }

    return ret;
}

std::string FileUtilsAndroid::getStringFromFile(const std::string& filename)
{
    Data data = getData(filename, true);
    if (data.isNull())
        return "";

    std::string ret((const char*)data.getBytes());
    return ret;
}
    
Data FileUtilsAndroid::getDataFromFile(const std::string& filename)
{
    return getData(filename, false);
}

unsigned char* FileUtilsAndroid::getFileData(const std::string& filename, const char* mode, ssize_t * size)
{    
    unsigned char * data = 0;
    
    if ( filename.empty() || (! mode) )
    {
        return 0;
    }
    
    string fullPath = fullPathForFilename(filename);
    
    if (fullPath[0] != '/')
    {
        string relativePath = string();

        size_t position = fullPath.find("assets/");
        if (0 == position) {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath += fullPath.substr(strlen("assets/"));
        } else {
            relativePath += fullPath;
        }
        LOGD("relative path = %s", relativePath.c_str());

        if (nullptr == FileUtilsAndroid::assetmanager) {
            LOGD("... FileUtilsAndroid::assetmanager is nullptr");
            return nullptr;
        }

        // read asset data
        AAsset* asset =
            AAssetManager_open(FileUtilsAndroid::assetmanager,
                               relativePath.c_str(),
                               AASSET_MODE_UNKNOWN);
        if (nullptr == asset) {
            LOGD("asset is nullptr");
            return nullptr;
        }

        off_t fileSize = AAsset_getLength(asset);

        data = (unsigned char*) malloc(fileSize);

        int bytesread = AAsset_read(asset, (void*)data, fileSize);
        if (size)
        {
            *size = bytesread;
        }

        AAsset_close(asset);
    }
    else
    {
        do
        {
            // read rrom other path than user set it
            //CCLOG("GETTING FILE ABSOLUTE DATA: %s", filename);
            FILE *fp = fopen(fullPath.c_str(), mode);
            CC_BREAK_IF(!fp);
            
            long fileSize;
            fseek(fp,0,SEEK_END);
            fileSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            data = (unsigned char*) malloc(fileSize);
            fileSize = fread(data,sizeof(unsigned char), fileSize,fp);
            fclose(fp);
            
            if (size)
            {
                *size = fileSize;
            }
        } while (0);
    }
    
    if (! data)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return data;
}

string FileUtilsAndroid::getWritablePath() const
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = getFileDirectoryJNI();

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
