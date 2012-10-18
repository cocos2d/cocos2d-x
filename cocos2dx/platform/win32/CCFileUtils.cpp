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
#include <windows.h>
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
        _CheckPath();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }

    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    bool bFileExist = true;
    const char* resDir = m_obDirectory.c_str();
    CCString* pRet = CCString::create("");

    const std::string& resourceRootPath = CCApplication::sharedApplication()->getResourceRootPath();
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        // path start with "x:", is absolute path
        pRet->m_sString = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0
        && ('/' == pszRelativePath[0] || '\\' == pszRelativePath[0]))
    {
        // path start with '/' or '\', is absolute path without driver name
        char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
        pRet->m_sString = szDriver;
        pRet->m_sString += pszRelativePath;
    }
    else if (resourceRootPath.length() > 0)
    {
        pRet->m_sString = resourceRootPath.c_str();
        pRet->m_sString += m_obDirectory.c_str();
        pRet->m_sString += pszRelativePath;
    }
    else
    {
        pRet->m_sString = s_pszResourcePath;
        pRet->m_sString += resDir;
        pRet->m_sString += pszRelativePath;
    }

    // If file or directory doesn't exist, try to find it in the root path.
    if (GetFileAttributesA(pRet->m_sString.c_str()) == -1)
    {
        pRet->m_sString = s_pszResourcePath;
        pRet->m_sString += pszRelativePath;

        if (GetFileAttributesA(pRet->m_sString.c_str()) == -1)
        {
            bFileExist = false;
        }
    }

    if (!bFileExist)
    { // Can't find the file, return the relative path.
        pRet->m_sString = pszRelativePath;
    }

    return pRet->m_sString.c_str();
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    // std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = CCString::create("");
    pRet->m_sString = relativeFile.substr(0, relativeFile.find_last_of("/\\") + 1);
    pRet->m_sString += pszFilename;
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
