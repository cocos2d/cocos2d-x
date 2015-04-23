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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "CCFileUtils-win32.h"
#include "platform/CCCommon.h"
#include <Shlobj.h>
#include <cstdlib>

using namespace std;

NS_CC_BEGIN

#define CC_MAX_PATH  512

// The root path of resources, the character encoding is UTF-8.
// UTF-8 is the only encoding supported by cocos2d-x API.
static std::string s_resourcePath = "";

// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
static inline std::string convertPathFormatToUnixStyle(const std::string& path)
{
    std::string ret = path;
    int len = ret.length();
    for (int i = 0; i < len; ++i)
    {
        if (ret[i] == '\\')
        {
            ret[i] = '/';
        }
    }
    return ret;
}

static void _checkPath()
{
    if (0 == s_resourcePath.length())
    {
        WCHAR *pUtf16ExePath = nullptr;
        _get_wpgmptr(&pUtf16ExePath);

        // We need only directory part without exe
        WCHAR *pUtf16DirEnd = wcsrchr(pUtf16ExePath, L'\\');

        char utf8ExeDir[CC_MAX_PATH] = { 0 };
        int nNum = WideCharToMultiByte(CP_UTF8, 0, pUtf16ExePath, pUtf16DirEnd-pUtf16ExePath+1, utf8ExeDir, sizeof(utf8ExeDir), nullptr, nullptr);

        s_resourcePath = convertPathFormatToUnixStyle(utf8ExeDir);
    }
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsWin32();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsWin32");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsWin32::FileUtilsWin32()
{
}

bool FileUtilsWin32::init()
{
    _checkPath();
    _defaultResRootPath = s_resourcePath;
    return FileUtils::init();
}

bool FileUtilsWin32::isFileExistInternal(const std::string& strFilePath) const
{
    if (0 == strFilePath.length())
    {
        return false;
    }
    
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, _defaultResRootPath);
    }

    WCHAR utf16Buf[CC_MAX_PATH] = {0};
    MultiByteToWideChar(CP_UTF8, 0, strPath.c_str(), -1, utf16Buf, sizeof(utf16Buf)/sizeof(utf16Buf[0]));

    DWORD attr = GetFileAttributesW(utf16Buf);
    if(attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
        return false;   //  not a file
    return true;
}

bool FileUtilsWin32::isAbsolutePath(const std::string& strPath) const
{
    if (   (strPath.length() > 2 
        && ( (strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z') )
        && strPath[1] == ':') || (strPath[0] == '/' && strPath[1] == '/'))
    {
        return true;
    }
    return false;
}

static Data getData(const std::string& filename, bool forString)
{
    if (filename.empty())
    {
        return Data::Null;
    }

    unsigned char *buffer = nullptr;

    size_t size = 0;
    do
    {
        // read the file from hardware
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);

        WCHAR wszBuf[CC_MAX_PATH] = {0};
        MultiByteToWideChar(CP_UTF8, 0, fullPath.c_str(), -1, wszBuf, sizeof(wszBuf)/sizeof(wszBuf[0]));

        HANDLE fileHandle = ::CreateFileW(wszBuf, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
        CC_BREAK_IF(fileHandle == INVALID_HANDLE_VALUE);
        
        size = ::GetFileSize(fileHandle, nullptr);

        if (forString)
        {
            buffer = (unsigned char*) malloc(size + 1);
            buffer[size] = '\0';
        }
        else
        {
            buffer = (unsigned char*) malloc(size);
        }
        DWORD sizeRead = 0;
        BOOL successed = FALSE;
        successed = ::ReadFile(fileHandle, buffer, size, &sizeRead, nullptr);
        ::CloseHandle(fileHandle);

        if (!successed)
        {
            // should determine buffer value, or it will cause memory leak
            if (buffer)
            {
                free(buffer);
                buffer = nullptr;
            }    
        }
    } while (0);
    
    Data ret;

    if (buffer == nullptr || size == 0)
    {
        std::string msg = "Get data from file(";
        // Gets error code.
        DWORD errorCode = ::GetLastError();
        char errorCodeBuffer[20] = {0};
        snprintf(errorCodeBuffer, sizeof(errorCodeBuffer), "%d", errorCode);

        msg = msg + filename + ") failed, error code is " + errorCodeBuffer;
        CCLOG("%s", msg.c_str());

        if (buffer)
            free(buffer);
    }
    else
    {
        ret.fastSet(buffer, size);
    }
    return ret;
}

std::string FileUtilsWin32::getStringFromFile(const std::string& filename)
{
    Data data = getData(filename, true);
	if (data.isNull())
	{
		return "";
	}

    std::string ret((const char*)data.getBytes());
    return ret;
}
    
Data FileUtilsWin32::getDataFromFile(const std::string& filename)
{
    return getData(filename, false);
}

unsigned char* FileUtilsWin32::getFileData(const std::string& filename, const char* mode, ssize_t* size)
{
    unsigned char * pBuffer = nullptr;
    *size = 0;
    do
    {
        // read the file from hardware
        std::string fullPath = fullPathForFilename(filename);

        WCHAR wszBuf[CC_MAX_PATH] = {0};
        MultiByteToWideChar(CP_UTF8, 0, fullPath.c_str(), -1, wszBuf, sizeof(wszBuf)/sizeof(wszBuf[0]));

        HANDLE fileHandle = ::CreateFileW(wszBuf, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
        CC_BREAK_IF(fileHandle == INVALID_HANDLE_VALUE);
        
        *size = ::GetFileSize(fileHandle, nullptr);

        pBuffer = (unsigned char*) malloc(*size);
        DWORD sizeRead = 0;
        BOOL successed = FALSE;
        successed = ::ReadFile(fileHandle, pBuffer, *size, &sizeRead, nullptr);
        ::CloseHandle(fileHandle);

        if (!successed)
        {
            free(pBuffer);
            pBuffer = nullptr;
        }
    } while (0);
    
    if (! pBuffer)
    {
        std::string msg = "Get data from file(";
        // Gets error code.
        DWORD errorCode = ::GetLastError();
        char errorCodeBuffer[20] = {0};
        snprintf(errorCodeBuffer, sizeof(errorCodeBuffer), "%d", errorCode);

        msg = msg + filename + ") failed, error code is " + errorCodeBuffer;
        CCLOG("%s", msg.c_str());
    }
    return pBuffer;
}

std::string FileUtilsWin32::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const
{
    std::string unixFileName = convertPathFormatToUnixStyle(filename);
    std::string unixResolutionDirectory = convertPathFormatToUnixStyle(resolutionDirectory);
    std::string unixSearchPath = convertPathFormatToUnixStyle(searchPath);

    return FileUtils::getPathForFilename(unixFileName, unixResolutionDirectory, unixSearchPath);
}

std::string FileUtilsWin32::getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename) const
{
    std::string unixDirectory = convertPathFormatToUnixStyle(strDirectory);
    std::string unixFilename = convertPathFormatToUnixStyle(strFilename);
    
    return FileUtils::getFullPathForDirectoryAndFilename(unixDirectory, unixFilename);
}

string FileUtilsWin32::getWritablePath() const
{
    if (_writablePath.length())
    {
        return _writablePath;
    }

    // Get full path of executable, e.g. c:\Program Files (x86)\My Game Folder\MyGame.exe
    char full_path[CC_MAX_PATH + 1];
    ::GetModuleFileNameA(nullptr, full_path, CC_MAX_PATH + 1);

    // Debug app uses executable directory; Non-debug app uses local app data directory
//#ifndef _DEBUG
        // Get filename of executable only, e.g. MyGame.exe
        char *base_name = strrchr(full_path, '\\');

        if(base_name)
        {
            char app_data_path[CC_MAX_PATH + 1];

            // Get local app data directory, e.g. C:\Documents and Settings\username\Local Settings\Application Data
            if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, app_data_path)))
            {
                string ret((char*)app_data_path);

                // Adding executable filename, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame.exe
                ret += base_name;

                // Remove ".exe" extension, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame
                ret = ret.substr(0, ret.rfind("."));

                ret += "\\";

                // Create directory
                if (SUCCEEDED(SHCreateDirectoryExA(nullptr, ret.c_str(), nullptr)))
                {
                    return convertPathFormatToUnixStyle(ret);
                }
            }
        }
//#endif // not defined _DEBUG

    // If fetching of local app data directory fails, use the executable one
    string ret((char*)full_path);

    // remove xxx.exe
    ret =  ret.substr(0, ret.rfind("\\") + 1);

    ret = convertPathFormatToUnixStyle(ret);

    return ret;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

