/*
 * CCFileUtils_Linux.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */
#include "platform/CCCommon.h"
#include "ccMacros.h"
#define __CC_PLATFORM_FILEUTILS_CPP__
#include "platform/CCFileUtilsCommon_cpp.h"
#include "platform/CCFileUtils.h"
#include "CCApplication.h"
#include "cocoa/CCString.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

NS_CC_BEGIN

static CCFileUtils* s_pFileUtils = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }
    
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    if (pszRelativePath && pszRelativePath[0] == '/')
    {
        return pszRelativePath;
    }

    const char* pszRootPath = CCApplication::sharedApplication()->getResourceRootPath();

    CCString* pRet = CCString::create(pszRootPath);
    if (m_obDirectory.size() > 0)
    {
        pRet->m_sString += m_obDirectory.c_str();
    }

    if (pszRelativePath != NULL)
    {
        pRet->m_sString += pszRelativePath;
    }

    // check if file or path exist
    struct stat sts;
    if (stat(pRet->getCString(), &sts) == -1 && errno == ENOENT)
    {
        // find from "Resources/"
        pRet->m_sString.clear();
        pRet->m_sString = CCApplication::sharedApplication()->getResourceRootPath();
        pRet->m_sString += pszRelativePath;
        if (stat(pRet->getCString(), &sts) == -1 && errno == ENOENT)
        {
            return pszRelativePath;
        }
    }

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
	string fullPath = pszFileName;
	unsigned char * pData = 0;

	if (!pszFileName || !pszMode)
	{
		return 0;
	}

	do
	{
		fullPath = fullPathFromRelativePath(fullPath.c_str());
		// read rrom other path than user set it
		FILE *fp = fopen(fullPath.c_str(), pszMode);
		CC_BREAK_IF(!fp);

		fseek(fp,0,SEEK_END);
		*pSize = ftell(fp);
		fseek(fp,0,SEEK_SET);
		pData = new unsigned char[*pSize];
		*pSize = fread(pData,sizeof(unsigned char), *pSize,fp);
		fclose(fp);
	}while (0);

	if (! pData && isPopupNotify())
	{
		std::string title = "Notification";
		std::string msg = "Get data from file(";
		msg.append(fullPath.c_str()).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}
	return pData;

}

string CCFileUtils::getWriteablePath()
{
	//return current resource path
  return CCApplication::sharedApplication()->getResourceRootPath();
}

NS_CC_END
