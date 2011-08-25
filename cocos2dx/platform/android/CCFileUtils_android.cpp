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
#include "jni/SystemInfoJni.h"

// record the resource path
static string s_strResourcePath = "";
	
/*
 * This function is implemented for jni to set apk path.
 */
void CCFileUtils::setResourcePath(const char* pszResourcePath)
{
	CCAssert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
	
	string tmp(pszResourcePath);

	if ((! pszResourcePath) || tmp.find(".apk") == string::npos)
	{
		return;
	}

	s_strResourcePath = pszResourcePath;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	return pszRelativePath;
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
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
	unsigned char * pData = 0;
	string fullPath(pszFileName);

	if ((! pszFileName) || (! pszMode))
	{
		return 0;
	}

	if (pszFileName[0] != '/')
	{
		// read from apk
		fullPath.insert(0, "assets/");
		pData =  CCFileUtils::getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
	}
	else
	{
		do 
		{
			// read rrom other path than user set it
			FILE *fp = fopen(pszFileName, pszMode);
			CC_BREAK_IF(!fp);

			unsigned long size;
			fseek(fp,0,SEEK_END);
			size = ftell(fp);
			fseek(fp,0,SEEK_SET);
			pData = new unsigned char[size];
			size = fread(pData,sizeof(unsigned char), size,fp);
			fclose(fp);

			if (pSize)
			{
				*pSize = size;
			}			
		} while (0);		
	}

    if (! pData && getIsPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(fullPath.c_str()).append(") failed!");
        CCMessageBox(msg.c_str(), title.c_str());
    }

    return pData;
}

void CCFileUtils::setResource(const char* pszZipFileName)
{
    CCAssert(0, "Have not implement!");
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
{
    CCAssert(0, "Have not implement!");
    return 0;
}

string CCFileUtils::getWriteablePath()
{
	// the path is: /data/data/ + package name
	string dir("/data/data/");
	const char *tmp = getPackageNameJNI();

	if (tmp)
	{
		dir.append(tmp).append("/");

		return dir;
	}
	else
	{
		return "";
	}
}

NS_CC_END;
