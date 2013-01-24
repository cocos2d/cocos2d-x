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
#include <Shlobj.h>
#include "CCDirector.h"
#include "CCApplication.h"

using namespace std;

NS_CC_BEGIN

// record the resource path
static char s_pszResourcePath[MAX_PATH] = {0};

static void _CheckPath()
{
    if (! s_pszResourcePath[0])
    {
        WCHAR  wszPath[MAX_PATH] = {0};
        int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath,
            GetCurrentDirectoryW(sizeof(wszPath), wszPath),
            s_pszResourcePath, MAX_PATH, NULL, NULL);
        s_pszResourcePath[nNum] = '\\';
    }
}

static CCFileUtils* s_pFileUtils = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
        s_pFileUtils->init();
        _CheckPath();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
        CC_SAFE_RELEASE(s_pFileUtils->m_pSearchPathArray);
        CC_SAFE_RELEASE(s_pFileUtils->m_pSearchResolutionsOrderArray);
    }

    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

bool CCFileUtils::init()
{
    m_pSearchPathArray = new CCArray();
    m_pSearchPathArray->addObject(CCString::create(""));

    m_pSearchResolutionsOrderArray = new CCArray();
    m_pSearchResolutionsOrderArray->addObject(CCString::create(""));

    return true;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return fullPathForFilename(pszRelativePath);
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string ret;
    const std::string& resourceRootPath = CCApplication::sharedApplication()->getResourceRootPath();

    if (filename.length() > 0
        && ('/' == filename[0] || '\\' == filename[0]))
    {
        // path start with '/' or '\', is absolute path without driver name
        char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
        ret = szDriver;
        ret += "/";
    }
    else if (resourceRootPath.length() > 0)
    {
       ret = resourceRootPath;
       if (ret[ret.length()-1] != '\\' && ret[ret.length()-1] != '/')
       {
            ret += "/";
       }
    }
    else
    {
       ret = s_pszResourcePath;
    }

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

    return ret;
}

const char* CCFileUtils::fullPathForFilename(const char* pszFileName)
{
	bool bFound = false;
    CCString* pRet = CCString::create("");

    std::string newFileName = getNewFilename(pszFileName);
    std::string fullpath;

    do 
    {
        if ((newFileName.length() > 1 && newFileName[1] == ':'))
        {
            // path start with "x:", is absolute path
            pRet->m_sString = newFileName;
            // return directly
            return pRet->getCString();
        }

        
        CCObject* pSearchObj = NULL;
        CCARRAY_FOREACH(m_pSearchPathArray, pSearchObj)
        {
            CCString* pSearchPath = (CCString*)pSearchObj;

            CCObject* pResourceDirObj = NULL;
            CCARRAY_FOREACH(m_pSearchResolutionsOrderArray, pResourceDirObj)
            {
                CCString* pResourceDirectory = (CCString*)pResourceDirObj;
                // Search in subdirectories
                fullpath = this->getPathForFilename(newFileName, pResourceDirectory->getCString(), pSearchPath->getCString());

                if (GetFileAttributesA(fullpath.c_str()) != -1)
                {
					pRet->m_sString = fullpath;
                    bFound = true;
                    break;
                }
            }
            if (bFound)
            {
                break;
            }
        }

    }while(false);
    
    if (!bFound)
    { // Can't find the file, return the relative path.
        pRet->m_sString = newFileName;
    }

    return pRet->getCString();
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

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    //std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = CCString::create("");
    pRet->m_sString = relativeFile.substr(0, relativeFile.find_last_of("/\\") + 1);
    pRet->m_sString += getNewFilename(pszFilename);
    return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long* pSize)
{
    unsigned char* pBuffer = NULL;
    CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invaild parameters.");
    *pSize = 0;
    do
    {
        // read the file from hardware
        FILE *fp = fopen(pszFileName, pszMode);
        CC_BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    if (! pBuffer && isPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");

        CCMessageBox(msg.c_str(), title.c_str());
    }
    return pBuffer;
}

string CCFileUtils::getWriteablePath()
{
	// Get full path of executable, e.g. c:\Program Files (x86)\My Game Folder\MyGame.exe
	char full_path[_MAX_PATH + 1];
	::GetModuleFileNameA(NULL, full_path, _MAX_PATH + 1);

	// Debug app uses executable directory; Non-debug app uses local app data directory
#ifndef _DEBUG
		// Get filename of executable only, e.g. MyGame.exe
		char *base_name = strrchr(full_path, '\\');

		if(base_name)
		{
			char app_data_path[_MAX_PATH + 1];

			// Get local app data directory, e.g. C:\Documents and Settings\username\Local Settings\Application Data
			if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, app_data_path)))
			{
				string ret((char*)app_data_path);

				// Adding executable filename, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame.exe
				ret += base_name;

				// Remove ".exe" extension, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame
				ret = ret.substr(0, ret.rfind("."));

				ret += "\\";

				// Create directory
				if (SUCCEEDED(SHCreateDirectoryExA(NULL, ret.c_str(), NULL)))
				{
					return ret;
				}
			}
		}
#endif // not defined _DEBUG

	// If fetching of local app data directory fails, use the executable one
	string ret((char*)full_path);

	// remove xxx.exe
	ret =  ret.substr(0, ret.rfind("\\") + 1);

	return ret;
}

NS_CC_END
