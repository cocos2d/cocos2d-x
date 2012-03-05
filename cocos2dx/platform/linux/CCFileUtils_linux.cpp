/*
 * CCFileUtils_linux.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */
#include "CCCommon.h"
#include "ccMacros.h"

#include "CCFileUtils.h"
#include "CCString.h"

#include <unistd.h>

using namespace std;

NS_CC_BEGIN;

static string s_strResourcePath = "";

void CCFileUtils::setResourcePath(const char* pszResourcePath) {
	CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");

//	s_strResourcePath = pszResourcePath;
	/* Sets current directory */
	if(chdir(pszResourcePath) < 0)
	{
		CCLog("set base folder error");
	}
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath) {
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = s_strResourcePath + pszRelativePath;
	return pRet->m_sString.c_str();

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

	if (! pData && getIsPopupNotify())
	{
		std::string title = "Notification";
		std::string msg = "Get data from file(";
		msg.append(fullPath.c_str()).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}
	return pData;

}

void CCFileUtils::setResource(const char* pszZipFileName) {
	CCAssert(0, "Have not implement!");
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out) {
	CCAssert(0, "Have not implement!");
	return 0;
}

string CCFileUtils::getWriteablePath() {
	//return current resource path
	return s_strResourcePath;
}

NS_CC_END;
