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

#define __CC_PLATFORM_FILEUTILS_CPP__
#include <string>
#include "platform/CCFileUtilsCommon_cpp.h"
#include "support/zip_support/ZipUtils.h"
#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

using namespace std;

NS_CC_BEGIN

static CCFileUtils* s_pFileUtils = NULL;
// record the zip on the resource path
static ZipFile *s_pZipFile = NULL;
// The full path cache, key: relative path, value: full path.
static std::map<std::string, std::string> s_fullPathCache;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
        s_pFileUtils->init();
        std::string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "assets/");
    }
    return s_pFileUtils;
}

bool CCFileUtils::init()
{
    m_strDefaultResRootPath = "assets/";
    m_searchPathArray.push_back(m_strDefaultResRootPath);
    m_searchResolutionsOrderArray.push_back("");

    return true;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
    }

    CC_SAFE_DELETE(s_pZipFile);
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{
    s_fullPathCache.clear();
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return CCString::create(fullPathForFilename(pszRelativePath))->getCString();
}

std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");

    // Return directly if it's an absolute path.
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    std::string strFileName = pszFileName;
    if (pszFileName[0] == '/' || strFileName.find(m_strDefaultResRootPath) == 0)
    {
        //CCLOG("Return absolute path( %s ) directly.", pszFileName);
        return pszFileName;
    }
    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = s_fullPathCache.find(pszFileName);
    if (cacheIter != s_fullPathCache.end())
    {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }

    // Get the new file name.
    std::string newFilename = getNewFilename(pszFileName);

    string fullpath = "";

    bool bFound = false;

    for (std::vector<std::string>::iterator searchPathsIter = m_searchPathArray.begin();
         searchPathsIter != m_searchPathArray.end(); ++searchPathsIter) {
        for (std::vector<std::string>::iterator resOrderIter = m_searchResolutionsOrderArray.begin();
             resOrderIter != m_searchResolutionsOrderArray.end(); ++resOrderIter) {
    
            //CCLOG("\n\nSEARCHING: %s, %s, %s", newFilename.c_str(), resOrderIter->c_str(), searchPathsIter->c_str());
            fullpath = this->getPathForFilename(newFilename, *resOrderIter, *searchPathsIter);
            
            // Check whether file exists in apk.
            if (s_pZipFile->fileExists(fullpath))
            {
                bFound = true;
            } 
            else
            {
                FILE *fp = fopen(fullpath.c_str(), "r");
                if(fp)
                {
                    bFound = true;
                    fclose(fp);
                }
            }
            if (bFound)
            {
                // Using the filename passed in as key.
                s_fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
                //CCLOG("Returning path: %s", fullpath.c_str());
                return fullpath;
            }
        }
    }

    // The file wasn't found, return the file name passed in.
    return pszFileName;
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = CCString::create("");
    pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->m_sString += getNewFilename(pszFilename);
    return pRet->getCString();
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string file = filename;
    std::string file_path = "";
    size_t pos = filename.find_last_of("/");
    if (pos != std::string::npos)
    {
        file_path = filename.substr(0, pos+1);
        file = filename.substr(pos+1);
    }
    
  // searchPath + file_path + resourceDirectory
    std::string path = searchPath;
    if (path.size() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    path += file_path;
    path += resourceDirectory;
    
    if (path.size() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    path += file;

    //CCLOG("getPathForFilename, fullPath = %s", path.c_str());
    return path;
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
    unsigned char * pData = 0;

    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }

    if (pszFileName[0] != '/')
    {
        //CCLOG("GETTING FILE RELATIVE DATA: %s", pszFileName);
        string fullPath = fullPathForFilename(pszFileName);
        pData = s_pZipFile->getFileData(fullPath.c_str(), pSize);
    }
    else
    {
        do 
        {
            // read rrom other path than user set it
	        //CCLOG("GETTING FILE ABSOLUTE DATA: %s", pszFileName);
            FILE *fp = fopen(pszFileName, pszMode);
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

    if (! pData && isPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCMessageBox(msg.c_str(), title.c_str());
    }

    return pData;
}

void CCFileUtils::setResourceDirectory(const char* pszResourceDirectory)
{
    if (pszResourceDirectory == NULL) return;
    m_obDirectory = pszResourceDirectory;
    std::vector<std::string> searchPaths = this->getSearchPaths();;
    searchPaths.insert(searchPaths.begin(), pszResourceDirectory);
    this->setSearchPaths(searchPaths);
}

void CCFileUtils::setSearchPaths(const std::vector<std::string>& searchPaths)
{
    bool bExistDefaultRootPath = false;

    m_searchPathArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); ++iter)
    {
        std::string strPrefix;
        std::string path;
        if ((*iter)[0] != '/')
        { // Not an absolute path
            if (iter->find(m_strDefaultResRootPath) != 0)
            { // The path contains no default resource root path, insert the root path.
                strPrefix = m_strDefaultResRootPath;
            }
        }
        path = strPrefix+(*iter);
        if (path.length() > 0 && path[path.length()-1] != '/')
        {
            path += "/";
        }
        if (!bExistDefaultRootPath && path == m_strDefaultResRootPath)
        {
            bExistDefaultRootPath = true;
        }
        m_searchPathArray.push_back(path);
    }

    if (!bExistDefaultRootPath)
    {
        //CCLOG("Default root path doesn't exist, adding it.");
        m_searchPathArray.push_back(m_strDefaultResRootPath);
    }
}

string CCFileUtils::getWriteablePath()
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    const char *tmp = getCacheDirectoryJNI();

    if (tmp)
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
