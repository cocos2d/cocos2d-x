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
#include "CCString.h"

#include <unistd.h>

using namespace std;

#define CC_RETINA_DISPLAY_FILENAME_SUFFIX "-hd"
#define CC_IPAD_FILENAME_SUFFIX "-ipad"
#define CC_IPAD_DISPLAY_RETINA_SUPPFIX "-ipadhd"


NS_CC_BEGIN

static string s_strResourcePath = "";

static CCFileUtils* s_pFileUtils = NULL;

static void _CheckPath()
{
//    if (! s_pszResourcePath[0])
//    {
//        WCHAR  wszPath[MAX_PATH];
//        int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath, 
//            GetCurrentDirectoryW(sizeof(wszPath), wszPath), 
//            s_pszResourcePath, MAX_PATH, NULL, NULL);
//        s_pszResourcePath[nNum] = '\\';
//    }
}

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

void CCFileUtils::setResourcePath(const char* pszResourcePath) {
	CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");

//	s_strResourcePath = pszResourcePath;
	/* Sets current directory */
	if(chdir(pszResourcePath) < 0)
	{
		CCLog("set base folder error");
	}
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath, ccResolutionType *pResolutionType)
{
	return pszRelativePath;
//	CCString* pRet = new CCString();
//	pRet->autorelease();
//	pRet->m_sString = s_strResourcePath + pszRelativePath;
//  return pRet->m_sString.c_str();
	//TODO fullPathFromRelativePath
	/*
    _CheckPath();

    CCString * pRet = new CCString();
    pRet->autorelease();
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        // path start with "x:", is absolute path
        pRet->m_sString = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0 
        && ('/' == pszRelativePath[0] || '\\' == pszRelativePath[0]))
    {
        // path start with '/' or '\', is absolute path without driver name
        char szDriver[3] = {s_strResourcePath[0], s_strResourcePath[1], 0};
        pRet->m_sString = szDriver;
        pRet->m_sString += pszRelativePath;
    }
    else
    {
        pRet->m_sString = s_strResourcePath;
        pRet->m_sString += pszRelativePath;
    }

    // is ipad?
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    bool isIpad = (winSize.width == 1024 || winSize.height == 768);

    std::string hiRes = pRet->m_sString.c_str();
    std::string::size_type pos = hiRes.find_last_of("/\\");
    std::string::size_type dotPos = hiRes.find_last_of(".");
    *pResolutionType = kCCResolutioniPhone;

    if (isIpad)
    {
        if (CC_CONTENT_SCALE_FACTOR() == 1.0f)
        {
            // ipad

            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_IPAD_FILENAME_SUFFIX);
            }
            else
            {
                hiRes.append(CC_IPAD_FILENAME_SUFFIX);
            }
            
            *pResolutionType = kCCResolutioniPad;
        }
        else
        {
            // ipad retina

            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_IPAD_DISPLAY_RETINA_SUPPFIX);
            }
            else
            {
                hiRes.append(CC_IPAD_DISPLAY_RETINA_SUPPFIX);
            }
            
            *pResolutionType = kCCResolutioniPadRetinaDisplay;
        }
    }
    else
    {    
        if (CC_CONTENT_SCALE_FACTOR() != 1.0f)
        {
            // iphone retina
            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            }
            else
            {
                hiRes.append(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            }
            
            *pResolutionType = kCCResolutioniPhoneRetinaDisplay;
        }
    }  

//    int attrib = GetFileAttributesA(hiRes.c_str());
//    if (attrib != INVALID_FILE_ATTRIBUTES && ! (FILE_ATTRIBUTE_DIRECTORY & attrib))
//    {
//        pRet->m_sString.swap(hiRes);
//    }
    return pRet->m_sString.c_str();
*/
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
	return s_strResourcePath;
}

NS_CC_END
