/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCFileUtilsAndroid.h"
#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"

#include <stdlib.h>

#define  LOG_TAG    "CCFileUtilsAndroid.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

static AAssetManager* s_assetmanager;

extern "C" {
    JNIEXPORT void JNICALL
    Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetAssetManager(JNIEnv* env,
                                                               jobject thiz,
                                                               jobject java_assetmanager) {
        AAssetManager* assetmanager =
            AAssetManager_fromJava(env, java_assetmanager);
        if (NULL == assetmanager) {
            LOGD("assetmanager : is NULL");
            return;
        }

        s_assetmanager = assetmanager;
    }
}

NS_CC_BEGIN

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new FileUtilsAndroid();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = NULL;
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

bool FileUtilsAndroid::isFileExist(const std::string& strFilePath)
{
    if (0 == strFilePath.length())
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

        if (s_assetmanager) {
            AAsset* aa = AAssetManager_open(s_assetmanager, s, AASSET_MODE_UNKNOWN);
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

bool FileUtilsAndroid::isAbsolutePath(const std::string& strPath)
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


unsigned char* FileUtilsAndroid::getFileData(const char* filename, const char* pszMode, unsigned long * pSize)
{    
    return doGetFileData(filename, pszMode, pSize, false);
}

unsigned char* FileUtilsAndroid::getFileDataForAsync(const char* filename, const char* pszMode, unsigned long * pSize)
{
    return doGetFileData(filename, pszMode, pSize, true);
}

unsigned char* FileUtilsAndroid::doGetFileData(const char* filename, const char* pszMode, unsigned long * pSize, bool forAsync)
{
    unsigned char * pData = 0;
    
    if ((! filename) || (! pszMode) || 0 == strlen(filename))
    {
        return 0;
    }
    
    string fullPath = fullPathForFilename(filename);
    
    if (fullPath[0] != '/')
    {
        
        string fullPath(filename);
        // fullPathForFilename is not thread safe.
        if (! forAsync)
        {
            fullPath = fullPathForFilename(filename);
        }

        const char* relativepath = fullPath.c_str();

        // "assets/" is at the beginning of the path and we don't want it
        relativepath += strlen("assets/");

        if (NULL == s_assetmanager) {
            LOGD("... s_assetmanager is NULL");
            return NULL;
        }

        // read asset data
        AAsset* asset =
            AAssetManager_open(s_assetmanager,
                               relativepath,
                               AASSET_MODE_UNKNOWN);
        if (NULL == asset) {
            LOGD("asset : is NULL");
            return NULL;
        }

        off_t size = AAsset_getLength(asset);

        pData = new unsigned char[size];

        int bytesread = AAsset_read(asset, (void*)pData, size);
        if (pSize)
        {
            *pSize = bytesread;
        }

        AAsset_close(asset);
    }
    else
    {
        do
        {
            // read rrom other path than user set it
	        //CCLOG("GETTING FILE ABSOLUTE DATA: %s", filename);
            FILE *fp = fopen(fullPath.c_str(), pszMode);
            CC_BREAK_IF(!fp);
            
            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);
            
            if (pSize)
            {
                *pSize = size;
            }
        } while (0);
    }
    
    if (! pData)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return pData;
}

string FileUtilsAndroid::getWritablePath()
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
