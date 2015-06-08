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
