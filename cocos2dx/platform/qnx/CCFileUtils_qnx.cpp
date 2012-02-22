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

#include "CCFileUtils.h"
#include "CCCommon.h"
#include "CCString.h"
#include <string>
#include <unistd.h>

NS_CC_BEGIN;

#define  MAX_PATH 256

// record the resource path
static std::string s_strResourcePath = "";
static std::string s_pszZipFilePath  = "";

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
    CCAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

    if (!pszResourcePath)
    	return;

    s_strResourcePath = pszResourcePath;

	// if the path is not ended with '/', append it
	if (s_strResourcePath.find("/") != (strlen(s_strResourcePath.c_str()) - 1))
	{
		s_strResourcePath += "/";
	}
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	// It works like this: if the relative path already includes the resource path
	// it will be returned as it is
	const std::string relPath = pszRelativePath;
	if (relPath.find(s_strResourcePath) == std::string::npos) 
    {
		CCString *pRet = new CCString();
		pRet->autorelease();
		pRet->m_sString = s_strResourcePath + pszRelativePath;
		return pRet->m_sString.c_str();
	}
	else 
    {
		return pszRelativePath;
	}
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
	unsigned char * buffer = NULL;

	std::string full_path = pszFileName;

	// If it is not inside resource path
	if (full_path.find(s_strResourcePath) == std::string::npos) 
    {
			full_path = s_strResourcePath + pszFileName;
	}

	// if specify the zip file,load from it first
	if (s_pszZipFilePath[0] != 0)
	{
		buffer = getFileDataFromZip(s_pszZipFilePath.c_str(), full_path.c_str(), pSize);
	}

	// if that failed then let's try and load the file ourselves
	if (!buffer)
	{
		// read the file from hardware
		FILE *fp = fopen(full_path.c_str(), pszMode);
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			*pSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			buffer = new unsigned char[*pSize];
			*pSize = fread(buffer, sizeof(unsigned char), *pSize, fp);
			fclose(fp);
		}
	}

	// we couldn't find the file
	if (!buffer && getIsPopupNotify())
	{
		std::string title = "Notification";
		std::string msg = "Get data from file(";
		msg.append(full_path);
		if (s_pszZipFilePath[0] != 0)
		{
			msg.append(") in zip archive(").append(s_pszZipFilePath);
		}
		msg.append(") failed!");

		CCMessageBox(msg.c_str(), title.c_str());
	}

	return buffer;
}

void CCFileUtils::setResource(const char* pszZipFileName)
{
    s_pszZipFilePath = pszZipFileName;
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
{
    CCAssert(0, "Have not implemented!");
    return 0;
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
