/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#include "CCFileUtilsWinRT.h"
#include <regex>
#include "CCWinRTUtils.h"
#include "platform/CCCommon.h"
using namespace std;

NS_CC_BEGIN

static std::string s_pszResourcePath;

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

static std::wstring StringUtf8ToWideChar(const std::string& strUtf8)
{
    std::wstring ret;
    if (!strUtf8.empty())
    {
        int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
        if (nNum)
        {
            WCHAR* wideCharString = new WCHAR[nNum + 1];
            wideCharString[0] = 0;

            nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

            ret = wideCharString;
            delete[] wideCharString;
        }
        else
        {
            CCLOG("Wrong convert to WideChar code:0x%x", GetLastError());
        }
    }
    return ret;
}

static std::string StringWideCharToUtf8(const std::wstring& strWideChar)
{
    std::string ret;
    if (!strWideChar.empty())
    {
        int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
        if (nNum)
        {
            char* utf8String = new char[nNum + 1];
            utf8String[0] = 0;

            nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

            ret = utf8String;
            delete[] utf8String;
        }
        else
        {
            CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
        }
    }

    return ret;
}

static std::string UTF8StringToMultiByte(const std::string& strUtf8)
{
    std::string ret;
    if (!strUtf8.empty())
    {
        std::wstring strWideChar = StringUtf8ToWideChar(strUtf8);
        int nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
        if (nNum)
        {
            char* ansiString = new char[nNum + 1];
            ansiString[0] = 0;

            nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, ansiString, nNum + 1, nullptr, FALSE);

            ret = ansiString;
            delete[] ansiString;
        }
        else
        {
            CCLOG("Wrong convert to Ansi code:0x%x", GetLastError());
        }
    }

    return ret;
}

static void _checkPath()
{
    if (s_pszResourcePath.empty())
    {
        // TODO: needs to be tested
        s_pszResourcePath = convertPathFormatToUnixStyle(CCFileUtilsWinRT::getAppPath() + '\\' + "Assets\\Resources" + '\\');
    }
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsWinRT();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = NULL;
          CCLOG("ERROR: Could not init CCFileUtilsWinRT");
        }
    }
    return s_sharedFileUtils;
}

CCFileUtilsWinRT::CCFileUtilsWinRT()
{
}

bool CCFileUtilsWinRT::init()
{
    _checkPath();
    _defaultResRootPath = s_pszResourcePath;
    return FileUtils::init();
}

std::string CCFileUtilsWinRT::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const
{
    std::string unixFileName = convertPathFormatToUnixStyle(filename);
    std::string unixResolutionDirectory = convertPathFormatToUnixStyle(resolutionDirectory);
    std::string unixSearchPath = convertPathFormatToUnixStyle(searchPath);

    return FileUtils::getPathForFilename(unixFileName, unixResolutionDirectory, unixSearchPath);
}

std::string CCFileUtilsWinRT::getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename) const
{
    std::string unixDirectory = convertPathFormatToUnixStyle(strDirectory);
    std::string unixFilename = convertPathFormatToUnixStyle(strFilename);
    return FileUtils::getFullPathForDirectoryAndFilename(unixDirectory, unixFilename);
}

std::string CCFileUtilsWinRT::getSuitableFOpen(const std::string& filenameUtf8) const
{
    return UTF8StringToMultiByte(filenameUtf8);
}

bool CCFileUtilsWinRT::isFileExistInternal(const std::string& strFilePath) const
{
    bool ret = false;
    FILE * pf = 0;

    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, _defaultResRootPath);
    }

    strPath = getSuitableFOpen(strPath);

    if (!strPath.empty() && (pf = fopen(strPath.c_str(), "rb")))
    {
        ret = true;
        fclose(pf);
    }
    return ret;
}

bool CCFileUtilsWinRT::isDirectoryExistInternal(const std::string& dirPath) const
{
    WIN32_FILE_ATTRIBUTE_DATA wfad;
    std::wstring wdirPath(dirPath.begin(), dirPath.end());
    if (GetFileAttributesEx(wdirPath.c_str(), GetFileExInfoStandard, &wfad))
    {
        return true;
    }
    return false;
}

bool CCFileUtilsWinRT::createDirectory(const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid path");

    if (isDirectoryExist(path))
        return true;

    // Split the path
    size_t start = 0;
    size_t found = path.find_first_of("/\\", start);
    std::string subpath;
    std::vector<std::string> dirs;

    if (found != std::string::npos)
    {
        while (true)
        {
            subpath = path.substr(start, found - start + 1);
            if (!subpath.empty())
                dirs.push_back(subpath);
            start = found + 1;
            found = path.find_first_of("/\\", start);
            if (found == std::string::npos)
            {
                if (start < path.length())
                {
                    dirs.push_back(path.substr(start));
                }
                break;
            }
        }
    }

    WIN32_FILE_ATTRIBUTE_DATA wfad;
    std::wstring wpath(path.begin(), path.end());
    if (!(GetFileAttributesEx(wpath.c_str(), GetFileExInfoStandard, &wfad)))
    {
        subpath = "";
        for (unsigned int i = 0; i < dirs.size(); ++i)
        {
            subpath += dirs[i];
            if (i > 0 && !isDirectoryExist(subpath))
            {
                std::wstring wsubpath(subpath.begin(), subpath.end());
                BOOL ret = CreateDirectory(wsubpath.c_str(), NULL);
                if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool CCFileUtilsWinRT::removeDirectory(const std::string& path)
{
    std::wstring wpath = std::wstring(path.begin(), path.end());
    std::wstring files = wpath + L"*.*";
    WIN32_FIND_DATA wfd;
    HANDLE  search = FindFirstFileEx(files.c_str(), FindExInfoStandard, &wfd, FindExSearchNameMatch, NULL, 0);
    bool ret = true;
    if (search != INVALID_HANDLE_VALUE)
    {
        BOOL find = true;
        while (find)
        {
            //. ..
            if (wfd.cFileName[0] != '.')
            {
                std::wstring temp = wpath + wfd.cFileName;
                if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    temp += '/';
                    ret = ret && this->removeDirectory(std::string(temp.begin(), temp.end()));
                }
                else
                {
                    SetFileAttributes(temp.c_str(), FILE_ATTRIBUTE_NORMAL);
                    ret = ret && DeleteFile(temp.c_str());
                }
            }
            find = FindNextFile(search, &wfd);
        }
        FindClose(search);
    }
    if (ret && RemoveDirectory(wpath.c_str()))
    {
        return true;
    }
    return false;
}

bool CCFileUtilsWinRT::isAbsolutePath(const std::string& strPath) const
{
    if (   strPath.length() > 2
        && ( (strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z') )
        && strPath[1] == ':')
    {
        return true;
    }
    return false;
}

bool CCFileUtilsWinRT::removeFile(const std::string &path)
{
    std::wstring wpath(path.begin(), path.end());
    if (DeleteFile(wpath.c_str()))
    {
        return true;
    }
    return false;
}

bool CCFileUtilsWinRT::renameFile(const std::string &oldfullpath, const std::string& newfullpath)
{
    CCASSERT(!oldfullpath.empty(), "Invalid path");
    CCASSERT(!newfullpath.empty(), "Invalid path");

    std::wstring oldfile(oldfullpath.begin(), oldfullpath.end());
    std::wstring newfile(newfullpath.begin(), newfullpath.end());

    if (MoveFileEx(oldfile.c_str(), newfile.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    {
        return true;
    }
    CCLOG("Rename failed with error: %d", GetLastError());
    return false;
}

bool CCFileUtilsWinRT::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    CCASSERT(!path.empty(), "Invalid path");
    std::string oldPath = path + oldname;
    std::string newPath = path + name;

    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");
    return renameFile(_old, _new);
}

static Data getData(const std::string& filename, bool forString)
{
    if (filename.empty())
    {
        CCASSERT(!filename.empty(), "Invalid filename!");
    }

    Data ret;
    unsigned char* buffer = nullptr;
    ssize_t size = 0;
    const char* mode = nullptr;
    mode = "rb";

    do
    {
        // Read the file from hardware
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
        FILE *fp = fopen(fullPath.c_str(), mode);
        CC_BREAK_IF(!fp);
        fseek(fp,0,SEEK_END);
        size = ftell(fp);
        fseek(fp,0,SEEK_SET);

        if (forString)
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
            buffer[size] = '\0';
        }
        else
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
        }

        size = fread(buffer, sizeof(unsigned char), size, fp);
        fclose(fp);
    } while (0);

    if (nullptr == buffer || 0 == size)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    else
    {
        ret.fastSet(buffer, size);
    }

    return ret;
}

std::string CCFileUtilsWinRT::getStringFromFile(const std::string& filename)
{
    Data data = getData(filename, true);
    if (data.isNull())
    {
        return "";
    }
    std::string ret((const char*)data.getBytes());
    return ret;
}

string CCFileUtilsWinRT::getWritablePath() const
{
    auto localFolderPath = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
    return convertPathFormatToUnixStyle(std::string(PlatformStringToString(localFolderPath)) + '\\');
}

string CCFileUtilsWinRT::getAppPath()
{
    Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
    return convertPathFormatToUnixStyle(std::string(PlatformStringToString(package->InstalledLocation->Path)));
}

NS_CC_END
