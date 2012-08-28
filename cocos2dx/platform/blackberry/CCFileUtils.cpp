/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

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
#include "CCApplication.h"
#include <unistd.h>

NS_CC_BEGIN;

#define  MAX_PATH 256

static CCFileUtils *theFileUtils = 0;

CCFileUtils *CCFileUtils::sharedFileUtils()
{
	if (!theFileUtils)
		theFileUtils = new CCFileUtils();

	return theFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (theFileUtils != NULL)
    {
        theFileUtils->purgeCachedEntries();
    }

    CC_SAFE_DELETE(theFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

static std::string fullPathFromRelativePathThreadSafe(const char* pszRelativePath)
{
	bool bFileExist = true;
	std::string ret("");
	std::string strPathWithoutResDir("");
    const char* pszRootPath = CCApplication::sharedApplication()->getResourceRootPath();
    CCAssert(pszRootPath != NULL, "The resource root path must be set in the main.cpp");
    CCAssert(pszRelativePath != NULL, "Parameter can't be NULL!");

    std::string pstrRelativePath = pszRelativePath;
    // if the relative path contains root path, skip it.
    if (pstrRelativePath.find(pszRootPath) == std::string::npos)
    {
    	ret += pszRootPath;
    }

    strPathWithoutResDir = ret + pszRelativePath;

    const char* resDir = CCFileUtils::sharedFileUtils()->getResourceDirectory();

    if (resDir != NULL)
    {
    	std::string pstrRootPath = pszRootPath;
    	std::string pstrResourceFullPath = pstrRootPath + resDir;
    	// if the relative path contains root path and resource directory, skip it.
    	if (pstrRelativePath.find(pstrResourceFullPath.c_str()) == std::string::npos)
    	{
    		ret += resDir;
    	}
    }

    ret += pszRelativePath;

    // If file or directory doesn't exist, try to find it in the root path.
    if (access(ret.c_str(), F_OK) == -1)
    {
    	//CCLOG("file or directory(%s) in Resource Directory doesn't exist.", ret.c_str());
    	ret = strPathWithoutResDir;

        if (access(ret.c_str(), F_OK) == -1)
        {
        	//CCLOG("file or directory(%s) in Root Directory also doesn't exist.", ret.c_str());
            bFileExist = false;
        }
        else
        {
        	//CCLOG("(%s) in Root Directory exist.", ret.c_str());
        }
    }
    else
    {
    	//CCLOG("(%s) in Resource Directory exist.", ret.c_str());
    }

    if (!bFileExist)
    { // Can't find the file, return the relative path.
    	ret = pszRelativePath;
    	//CCLOG("Can't find the file, return the relative path(%s).", ret.c_str());
    }

	return ret;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	CCString* pRet = CCString::create("");
	std::string strFullPath = fullPathFromRelativePathThreadSafe(pszRelativePath);
	pRet->m_sString = strFullPath;
    return pRet->getCString();
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
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
	unsigned char *buffer = 0;
	std::string full_path(pszFileName);

	if (!pszFileName || !pszMode)
	{
		return 0;
	}

	do
	{
		full_path = fullPathFromRelativePathThreadSafe(full_path.c_str());
		// read from other path than user set it
		FILE *fp = fopen(full_path.c_str(), pszMode);
		CC_BREAK_IF(!fp);

		unsigned long size;
		fseek(fp,0,SEEK_END);
		size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		buffer = new unsigned char[size];
		size = fread(buffer, sizeof(unsigned char), size, fp);
		fclose(fp);

		if (pSize)
		{
			*pSize = size;
		}
	} while (0);

	if (!buffer && isPopupNotify())
	{
		std::string title = "Notification";
		std::string msg = "Get data from file(";
		msg.append(full_path.c_str()).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}

	return buffer;
}

std::string CCFileUtils::getWriteablePath()
{
	// Let's write it in the current working directory's data folder
	char cwd[FILENAME_MAX];

	getcwd(cwd, FILENAME_MAX - 1);
	cwd[FILENAME_MAX-1] = '\0';

	std::string path = cwd;
	path += "/data/";

	return path;
}

NS_CC_END;
