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
static std::map<std::string, std::string> s_fullPathCache;

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
		_CheckPath();
        s_pFileUtils = new CCFileUtils();
        s_pFileUtils->init();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
    }

    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{
    s_fullPathCache.clear();
}

bool CCFileUtils::init()
{
	m_strDefaultResRootPath = s_pszResourcePath;
    m_searchPathArray.push_back(m_strDefaultResRootPath);
    m_searchResolutionsOrderArray.push_back("");

    return true;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return CCString::create(fullPathForFilename(pszRelativePath))->getCString();
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

    return path;
}

std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
	CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");

    // Return directly if it's an absolute path.
    if (strlen(pszFileName) > 3 
        && pszFileName[0] >= 'a' && pszFileName[0] <= 'z'
        && pszFileName[0] >= 'A' && pszFileName[0] <= 'Z'
        && (pszFileName[1] == ':')
        && (pszFileName[2] == '\\' || pszFileName[2] == '/')
    )
    {
        //CCLOG("Probably invoking fullPathForFilename recursively, return the full path: %s", pszFileName);
        return pszFileName;
    }

    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = s_fullPathCache.find(pszFileName);
    if (cacheIter != s_fullPathCache.end()) {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }

    std::string newFileName = getNewFilename(pszFileName);
    std::string fullpath;
    
    for (std::vector<std::string>::iterator searchPathsIter = m_searchPathArray.begin();
         searchPathsIter != m_searchPathArray.end(); ++searchPathsIter) {
        for (std::vector<std::string>::iterator resOrderIter = m_searchResolutionsOrderArray.begin();
             resOrderIter != m_searchResolutionsOrderArray.end(); ++resOrderIter) {

            fullpath = this->getPathForFilename(newFileName, *resOrderIter, *searchPathsIter);

            if (GetFileAttributesA(fullpath.c_str()) != -1)
            {
                // Adding the full path to cache if the file was found.
                s_fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
				//CCLOG("Returning path: %s", fullpath.c_str());
                return fullpath;
            }
        }
    }

    // The file wasn't found, return the file name passed in.
    return pszFileName;
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
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
        std::string fullPath = fullPathForFilename(pszFileName);
        // read the file from hardware
        FILE *fp = fopen(fullPath.c_str(), pszMode);
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
		if (iter->length() > 1 && (*iter)[1] != ':')
		{ // Not an absolute path
			if (iter->find(m_strDefaultResRootPath) != 0)
			{ // The path contains no default resource root path, insert the root path.
				strPrefix = m_strDefaultResRootPath;
			}
		}
		path = strPrefix+(*iter);
		if (path.length() > 0 && path[path.length()-1] != '/' && path[path.length()-1] != '\\')
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
