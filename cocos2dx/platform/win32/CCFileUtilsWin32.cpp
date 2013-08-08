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
#include "CCFileUtilsWin32.h"
#include "platform/CCCommon.h"
#include <Shlobj.h>

using namespace std;

NS_CC_BEGIN

static char s_pszResourcePath[MAX_PATH] = {0};

static void _checkPath()
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

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsWin32();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsWin32::CCFileUtilsWin32()
{
}

bool CCFileUtilsWin32::init()
{
    _checkPath();
    m_strDefaultResRootPath = s_pszResourcePath;
    return CCFileUtils::init();
}

bool CCFileUtilsWin32::isFileExist(const std::string& strFilePath)
{
	std::string strFilePathAscii = utf8Togbk(strFilePath.c_str());
	if (0 == strFilePathAscii.length())
	{
		return false;
	}

	std::string strPath = strFilePathAscii;
	if (!isAbsolutePath(strPath))
	{ // Not absolute path, add the default root path at the beginning.
		strPath.insert(0, m_strDefaultResRootPath);
	}
	return GetFileAttributesA(strPath.c_str()) != -1 ? true : false;
}

bool CCFileUtilsWin32::isAbsolutePath(const std::string& strPath)
{
	std::string strPathAscii = utf8Togbk(strPath.c_str());
	if (strPathAscii.length() > 2 
		&& ( (strPathAscii[0] >= 'a' && strPathAscii[0] <= 'z') || (strPathAscii[0] >= 'A' && strPathAscii[0] <= 'Z') )
		&& strPathAscii[1] == ':')
	{
		return true;
	}
	return false;
}

std::string CCFileUtilsWin32::fullPathForFilename(const char* pszFileName)
{
	std:string pszFileNameAscii = utf8Togbk(pszFileName);
	return CCFileUtils::fullPathForFilename(pszFileNameAscii.c_str());
}

string CCFileUtilsWin32::getWritablePath()
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

void CCFileUtilsWin32::addSearchPath(const char* path)
{
	std::string strDes = utf8Togbk(path);
	CCFileUtils::addSearchPath(strDes.c_str());
}

void CCFileUtilsWin32::removeSearchPath(const char *path)
{
	std::string strDes = utf8Togbk(path);
	CCFileUtils::removeSearchPath(strDes.c_str());
}

std::string CCFileUtilsWin32::utf8Togbk(const char *src)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP,0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (strTemp.find('?') != std::string::npos)
	{
		strTemp.assign(src);
	}
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

std::string CCFileUtilsWin32::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath)
{
	std::string filenameAscii =  utf8Togbk(filename.c_str());
	std::string resolutionDirectoryAscii =  utf8Togbk(resolutionDirectory.c_str());
	std::string rearchPathAscii = utf8Togbk(searchPath.c_str());

	return CCFileUtils::getPathForFilename(filenameAscii, resolutionDirectoryAscii, rearchPathAscii);
}

NS_CC_END
