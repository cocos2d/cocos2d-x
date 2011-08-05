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

#define  MAX_PATH 256

using namespace std;

// record the resource path
static string s_strResourcePath = "";
	
void CCFileUtils::setResourcePath(const char* pszResourcePath)
{
	CCAssert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
	
	if (! pszResourcePath)
	{
		return;
	}
	
	s_strResourcePath = pszResourcePath;

	/*
	 * If the path is set by user, and not end with "/", append it
	 */
	if (s_strResourcePath.find(".apk") == string::npos 
		&& s_strResourcePath.find_last_of("/") != s_strResourcePath.length() - 1)
	{
		s_strResourcePath += "/";
	}
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	if (s_strResourcePath.find(".apk") != string::npos)
	{
		return pszRelativePath;
	}
	else
	{
		CCString *pRet = new CCString();
		pRet->autorelease();
		pRet->m_sString = s_strResourcePath + pszRelativePath;
		return pRet->m_sString.c_str();
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
	string fullPath = pszFileName;
	unsigned char * pData = 0;

	if (s_strResourcePath.find(".apk") != string::npos)
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

			fseek(fp,0,SEEK_END);
			*pSize = ftell(fp);
			fseek(fp,0,SEEK_SET);
			pData = new unsigned char[*pSize];
			*pSize = fread(pData,sizeof(unsigned char), *pSize,fp);
			fclose(fp);
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
	char* tmp = getPackageNameJNI();

	if (tmp)
	{
		dir.append(tmp).append("/");

		// release memory
		delete [] tmp;

		return dir;
	}
	else
	{
		return "";
	}
}

NS_CC_END;
