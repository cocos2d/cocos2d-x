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
#include "platform/CCFileUtilsCommon_cpp.h"
#include "support/zip_support/ZipUtils.h"

using namespace std;

NS_CC_BEGIN

#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

static CCFileUtils* s_pFileUtils = NULL;
// record the zip on the resource path
static ZipFile *s_pZipFile = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
        std::string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "assets/");
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }

    CC_SAFE_DELETE(s_pZipFile);
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return pszRelativePath;
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = new CCString();
    pRet->autorelease();
    pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->m_sString += pszFilename;
    return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
    unsigned char * pData = 0;
    string fullPath(pszFileName);

    if ((! pszFileName) || (! pszMode))
    {
        return 0;
    }

    if (pszFileName[0] != '/')
    {
        // read from apk
        string pathWithoutDirectory = fullPath;
        
        fullPath.insert(0, m_obDirectory.c_str());
        fullPath.insert(0, "assets/");
        pData = s_pZipFile->getFileData(fullPath, pSize);
        
        if (! pData && m_obDirectory.size() > 0)
        {
            // search from root
            pathWithoutDirectory.insert(0, "assets/");
            pData = s_pZipFile->getFileData(pathWithoutDirectory, pSize);
        }
    }
    else
    {
        do 
        {
            // read rrom other path than user set it
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
        msg.append(fullPath.c_str()).append(") failed!");
        CCMessageBox(msg.c_str(), title.c_str());
    }

    return pData;
}

string CCFileUtils::getWriteablePath()
{
    // the path is: /data/data/ + package name
    string dir("/data/data/");
    const char *tmp = getPackageNameJNI();

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
