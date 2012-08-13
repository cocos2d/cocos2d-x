/*
 * CCFileUtils_Linux.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */
#include "CCCommon.h"
#include "ccMacros.h"
#include "platform/CCFileUtilsCommon_cpp.h"
#include "CCFileUtils.h"
#include "CCApplication.h"
#include "CCString.h"
#include <unistd.h>

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
    const char* pszRootPath = CCApplication::sharedApplication().getResourceRootPath();

    CCString* pRet = CCString::create(pszRootPath);
    const char* resDir = CCFileUtils::sharedFileUtils()->getResourceDirectory();
    if (resDir != NULL)
    {
        pRet->m_sString += resDir;
    }

    if (pszRelativePath != NULL)
    {
        pRet->m_sString += pszRelativePath;
    }

    return pRet->getCString();
}


const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile) {
	std::string relativeFile = pszRelativeFile;
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += pszFilename;
	return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize) {

	string fullPath = pszFileName;
	unsigned char * pData = 0;

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

string CCFileUtils::getWriteablePath() {
	//return current resource path
  return CCApplication::sharedApplication().getResourceRootPath();
}

NS_CC_END
