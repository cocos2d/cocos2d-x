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

// record the resource path

#include "CCCommon.h"

using namespace std;

NS_CC_BEGIN;
// record the resource path
static string s_strResourcePath = "";

void CCFileUtils::setResourcePath(const char* pszResourcePath)
{
	CCAssert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
	s_strResourcePath = pszResourcePath;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	int len = 0;
	if (pszRelativePath == NULL || (len = strlen(pszRelativePath)) <= 0)
		return NULL;
	CCString * pRet = new CCString();
    pRet->autorelease();
    if (len > 1 && pszRelativePath[0] == '/')
    {
        pRet->m_sString = pszRelativePath;
    }
    else
    {
        pRet->m_sString = s_strResourcePath;
        pRet->m_sString += pszRelativePath;
    }
	return pRet->m_sString.c_str();
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += pszFilename;
	return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
	CC_ASSERT(pszFileName != NULL && pszMode != NULL);
    unsigned char * pData = 0;
    int len = 0;
    string fullPath;

    len = strlen(pszFileName);

    if (len > 1 && pszFileName[0] == '/')
    {
    	fullPath = pszFileName;
    }
    else
    {
    	fullPath = s_strResourcePath;
    	fullPath += pszFileName;
    }

    do 
    {
        // read rrom other path than user set it
        FILE *fp = fopen(fullPath.c_str(), pszMode);
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
    CC_UNUSED_PARAM(pszZipFileName);
    CCAssert(0, "Have not implement!");;
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
{
    CCAssert(0, "Have not implement!");
    return 0;
}

string CCFileUtils::getWriteablePath()
{
	return "/Home/";
}

NS_CC_END;

