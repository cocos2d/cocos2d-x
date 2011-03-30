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

NS_CC_BEGIN;

#include "CCCommon.h"

#define  MAX_PATH 256

// record the resource path
static std::string s_strRelativePath = "";
static std::string s_strResourcePath = "";
	
void CCFileUtils::setRelativePath(const char* pszRelativePath)
{
	CCAssert(pszRelativePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
	
	if (! pszRelativePath)
	{
		return;
	}
	
	s_strRelativePath = pszRelativePath;
	
	// if the path is not ended with '/', append it
	if (s_strRelativePath.find("/") != (strlen(s_strRelativePath.c_str()) - 1))
	{
		s_strRelativePath += "/";
	}
}

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
    CCAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

    s_strResourcePath = pszResourcePath;
}

const char* CCFileUtils::getResourcePath()
{
	return s_strResourcePath.c_str();
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	return pszRelativePath;
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	//std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
	std::string relativeFile = pszRelativeFile;
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += pszFilename;
	return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{	
	string fullPath = s_strRelativePath + pszFileName;
	unsigned char * pData =  CCFileUtils::getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
    if (! pData && getIsPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCMessageBox(msg.c_str(), title.c_str());
    }
    return pData;
}

void CCFileUtils::setResource(const char* pszZipFileName, const char* pszResPath)
{
    CCAssert(0, "Have not implement!");
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
{
    CCAssert(0, "Have not implement!");
    return 0;
}

NS_CC_END;
