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
        s_pFileUtils->init();
        std::string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "assets/");
    }
    return s_pFileUtils;
}

bool CCFileUtils::init()
{
    m_pSearchPathArray = new CCArray();
    m_pSearchPathArray->addObject(CCString::create("assets/"));
    m_pSearchPathArray->addObject(CCString::create(""));
    
    m_pSearchResolutionsOrderArray = new CCArray();
    m_pSearchResolutionsOrderArray->addObject(CCString::create(""));

    return true;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }
    CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
    CC_SAFE_RELEASE(s_pFileUtils->m_pSearchPathArray);
    CC_SAFE_RELEASE(s_pFileUtils->m_pSearchResolutionsOrderArray);
    CC_SAFE_DELETE(s_pZipFile);
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return fullPathForFilename(pszRelativePath);
}

const char* CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    if (pszFileName == NULL || pszFileName[0] == '\0') {
        return pszFileName;
    }

    return CCString::create(getNewFilename(pszFileName).c_str())->getCString();
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = new CCString();
    pRet->autorelease();
    pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->m_sString += getNewFilename(pszFilename);
    return pRet->m_sString.c_str();
}

void CCFileUtils::loadFilenameLookupDictionaryFromFile(const char* filename)
{
    const char* pFullPath = this->fullPathForFilename(filename);
    if (pFullPath)
    {
        CCDictionary* pDict = CCDictionary::createWithContentsOfFile(filename);
        if (pDict)
        {
            CCDictionary* pMetadata = (CCDictionary*)pDict->objectForKey("metadata");
            int version = ((CCString*)pMetadata->objectForKey("version"))->intValue();
            if (version != 1)
            {
                CCLOG("cocos2d: ERROR: Invalid filenameLookup dictionary version: %ld. Filename: %s", (long)version, filename);
                return;
            }
            
            setFilenameLookupDictionary((CCDictionary*)pDict->objectForKey("filenames"));
        }
    }
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string  ret = "";
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
    ret += path;

    CCLog("full path = %s", ret.c_str());
    return ret;
}


string CCFileUtils::getAbsoluteFilenamePath(const char *pszFileName) {

    string fullpath = "";
    if (pszFileName[0] != '/')
    {
        // read from apk
        bool bFound = false;
        CCObject* pSearchObj = NULL;
        CCARRAY_FOREACH(m_pSearchPathArray, pSearchObj)
        {
            CCString* pSearchPath = (CCString*)pSearchObj;
            
            CCObject* pResourceDirObj = NULL;
            CCARRAY_FOREACH(m_pSearchResolutionsOrderArray, pResourceDirObj)
            {
                CCString* pResourceDirectory = (CCString*)pResourceDirObj;
                // Search in subdirectories
		
		CCLOG("\n\nSEARCHING: %s, %s, %s", pszFileName, pResourceDirectory->getCString(), pSearchPath->getCString());
                fullpath = this->getPathForFilename(pszFileName, pResourceDirectory->getCString(), pSearchPath->getCString());
		
		unsigned char * pData = 0;
		unsigned long * pSize;
		pData = s_pZipFile->getFileData(fullpath.c_str(), pSize);
		if (pData)
		  {
		    bFound = true;
		  } else {
		  FILE *fp = fopen(fullpath.c_str(), "r");
		  if(fp) {
		    bFound = true;
		    fclose(fp);
		  }
		}
		if (bFound)
		  {
		    CCLOG("Returning path: %s", fullpath.c_str());
		    return fullpath;
		  }
	    }
	}
    } else {
      return pszFileName;
    }

    return "";
}


unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
    unsigned char * pData = 0;

    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }

    string fullpath;
                    
    string fullFilename = getAbsoluteFilenamePath(pszFileName);

    if (fullFilename[0] != '/') {
      CCLOG("GETTING FILE RELATIVE DATA: %s", pszFileName);
      pData = s_pZipFile->getFileData(fullFilename.c_str(), pSize);
    }
    else
    {
        do 
        {
            // read rrom other path than user set it
	  CCLOG("GETTING FILE ABSOLUTE DATA: %s", fullFilename.c_str());
            FILE *fp = fopen(fullFilename.c_str(), pszMode);
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
        msg.append(fullpath.c_str()).append(") failed!");
        CCMessageBox(msg.c_str(), title.c_str());
    }

    return pData;
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
