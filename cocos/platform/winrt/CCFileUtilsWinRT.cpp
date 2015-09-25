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
    std::wstring wdirPath = StringUtf8ToWideChar(dirPath);
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
    
    if (!(GetFileAttributesEx(StringUtf8ToWideChar(path).c_str(), GetFileExInfoStandard, &wfad)))
    {
        subpath = "";
        for (unsigned int i = 0; i < dirs.size(); ++i)
        {
            subpath += dirs[i];
            if (i > 0 && !isDirectoryExist(subpath))
            {
                BOOL ret = CreateDirectory(StringUtf8ToWideChar(subpath).c_str(), NULL);
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
    std::wstring wpath = StringUtf8ToWideChar(path);
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
    std::wstring wpath = StringUtf8ToWideChar(path);
    if (DeleteFile(wpath.c_str()))
    {
        return true;
    }
    else
    {
        CCLOG("Remove file failed with error: %d", GetLastError());
        return false;
    }
}

bool CCFileUtilsWinRT::renameFile(const std::string &oldfullpath, const std::string& newfullpath)
{
    CCASSERT(!oldfullpath.empty(), "Invalid path");
    CCASSERT(!newfullpath.empty(), "Invalid path");

    std::regex pat("\\/");
    std::string _oldfullpath = std::regex_replace(oldfullpath, pat, "\\");
    std::string _newfullpath = std::regex_replace(newfullpath, pat, "\\");

    std::wstring _wNewfullpath = StringUtf8ToWideChar(_newfullpath);

    if (FileUtils::getInstance()->isFileExist(_newfullpath))
    {
        if (!DeleteFile(_wNewfullpath.c_str()))
        {
            CCLOGERROR("Fail to delete file %s !Error code is 0x%x", newfullpath.c_str(), GetLastError());
        }
    }

    if (MoveFileEx(StringUtf8ToWideChar(_oldfullpath).c_str(), _wNewfullpath.c_str(),
        MOVEFILE_REPLACE_EXISTING & MOVEFILE_WRITE_THROUGH))
    {
        return true;
    }
    else
    {
        CCLOGERROR("Fail to rename file %s to %s !Error code is 0x%x", oldfullpath.c_str(), newfullpath.c_str(), GetLastError());
        return false;
    }
}

bool CCFileUtilsWinRT::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    CCASSERT(!path.empty(), "Invalid path");
    std::string oldPath = path + oldname;
    std::string newPath = path + name;

    return renameFile(oldPath, newPath);
}

std::string CCFileUtilsWinRT::getStringFromFile(const std::string& filename)
{
    Data data = getDataFromFile(filename);
    if (data.isNull())
    {
        return "";
    }
    std::string ret((const char*)data.getBytes(), data.getSize());
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
