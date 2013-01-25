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
        s_pFileUtils->init();
    }
    return s_pFileUtils;
}

bool CCFileUtils::init()
{
    m_pSearchPathArray = new CCArray();
    m_pSearchPathArray->addObject(CCString::create(""));
    
    m_pSearchResolutionsOrderArray = new CCArray();
    m_pSearchResolutionsOrderArray->addObject(CCString::create(""));

    return true;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
        CC_SAFE_RELEASE(s_pFileUtils->m_pSearchPathArray);
        CC_SAFE_RELEASE(s_pFileUtils->m_pSearchResolutionsOrderArray);
    }
    
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string ret;
    const std::string& resourceRootPath = CCApplication::sharedApplication()->getResourceRootPath();

    ret = resourceRootPath;
    if (ret[ret.length()-1] != '\\' && ret[ret.length()-1] != '/')
    {
        ret += "/";
    }

    std::string file = filename;
    std::string file_path = "";
    size_t pos = filename.find_last_of("/");
    if (pos != std::string::npos)
    {
        file_path = filename.substr(0, pos+1);
        file = filename.substr(pos+1);
    }

    // searchPath + file_path + resourceDirectory
    std::string path = searchPath;
    if (path.size() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    path += file_path;
    path += resourceDirectory;

    if (path.size() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    path += file;
    ret += path;

    return ret;
}

const char* CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    if (pszFileName && pszFileName[0] == '/')
    {
        return pszFileName;
    }

    bool bFound = false;
    CCString* pRet = CCString::create("");

    std::string newFileName = getNewFilename(pszFileName);
    std::string fullpath;

    do 
    {
        CCObject* pSearchObj = NULL;
        CCARRAY_FOREACH(m_pSearchPathArray, pSearchObj)
        {
            CCString* pSearchPath = (CCString*)pSearchObj;

            CCObject* pResourceDirObj = NULL;
            CCARRAY_FOREACH(m_pSearchResolutionsOrderArray, pResourceDirObj)
            {
                CCString* pResourceDirectory = (CCString*)pResourceDirObj;
                // Search in subdirectories
                fullpath = this->getPathForFilename(newFileName, pResourceDirectory->getCString(), pSearchPath->getCString());

                // check if file or path exist
                struct stat sts;
                if (stat(fullpath.c_str(), &sts) != -1)
                {
                    pRet->m_sString = fullpath;
                    bFound = true;
                    break;
                }
            }
            if (bFound)
            {
                break;
            }
        }

    }while(false);
    
    if (!bFound)
    { // Can't find the file, return the relative path.
        pRet->m_sString = newFileName;
    }

    return pRet->getCString();
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return fullPathForFilename(pszRelativePath);
}


const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	std::string relativeFile = pszRelativeFile;
	CCString *pRet = CCString::create("");
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += getNewFilename(pszFilename);
	return pRet->m_sString.c_str();
}

void CCFileUtils::loadFilenameLookupDictionaryFromFile(const char* filename)
{
    const char* pFullPath = this->fullPathForFilename(filename);
    if (pFullPath)
    {
        CCDictionary* pDict = CCDictionary::createWithContentsOfFile(filename);
        if (pDict)
        {
            CCDictionary* pMetadata = (CCDictionary*)pDict->objectForKey("metadata");
            int version = ((CCString*)pMetadata->objectForKey("version"))->intValue();
            if (version != 1)
            {
                CCLOG("cocos2d: ERROR: Invalid filenameLookup dictionary version: %ld. Filename: %s", (long)version, filename);
                return;
            }

            setFilenameLookupDictionary((CCDictionary*)pDict->objectForKey("filenames"));
        }
    }
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
	unsigned char * pData = 0;

	if (!pszFileName || !pszMode)
	{
		return 0;
	}

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
		msg.append(pszFileName).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}
	return pData;

}

void CCFileUtils::setResourceDirectory(const char* pszResourceDirectory)
{
    m_obDirectory = pszResourceDirectory;
    if (m_obDirectory.size() > 0 && m_obDirectory[m_obDirectory.size() - 1] != '/')
    {
        m_obDirectory.append("/");
    }
    m_pSearchPathArray->insertObject(CCString::create(m_obDirectory.c_str()), 0);
}

string CCFileUtils::getWriteablePath()
{
	//return current resource path
  return CCApplication::sharedApplication()->getResourceRootPath();
}

NS_CC_END
