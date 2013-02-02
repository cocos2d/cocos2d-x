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
static std::map<std::string, std::string> s_fullPathCache;

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
    // get application path
    int length = 0;
    char fullpath[256] = {0};
    length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));
    fullpath[length] = '\0';

    std::string resourcePath = fullpath;
    resourcePath = resourcePath.substr(0, resourcePath.find_last_of("/"));
    resourcePath += "/../../../Resources/";
    m_strDefaultResRootPath = resourcePath;
    //CCLOG("DEFAULT RES PATH = %s", m_strDefaultResRootPath.c_str());
    m_searchPathArray.push_back(m_strDefaultResRootPath);
    m_searchResolutionsOrderArray.push_back("");

    return true;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
    }
    
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{
    s_fullPathCache.clear();
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
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

    return path;
}

std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");

    // Return directly if it's an absolute path.
    if (pszFileName[0] == '/')
    {
        //CCLOG("return absolute path directly: %s ", pszFileName);
        return pszFileName;
    }

    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = s_fullPathCache.find(pszFileName);
    if (cacheIter != s_fullPathCache.end()) {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }

    // in Lookup Filename dictionary ?
    std::string newFileName = getNewFilename(pszFileName);

    std::string fullpath;

    for (std::vector<std::string>::iterator searchPathsIter = m_searchPathArray.begin();
         searchPathsIter != m_searchPathArray.end(); ++searchPathsIter) {
        for (std::vector<std::string>::iterator resOrderIter = m_searchResolutionsOrderArray.begin();
             resOrderIter != m_searchResolutionsOrderArray.end(); ++resOrderIter) {

            //CCLOG("\n\nSEARCHING: %s, %s, %s", newFileName.c_str(), resOrderIter->c_str(), searchPathsIter->c_str());

            fullpath = this->getPathForFilename(newFileName, *resOrderIter, *searchPathsIter);

            // check if file or path exist
            struct stat sts;
            if (stat(fullpath.c_str(), &sts) != -1)
            {
                // Adding the full path to cache if the file was found.
                s_fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
                //CCLOG("Returning path: %s", fullpath.c_str());
                return fullpath;
            }
        }
    }

    // The file wasn't found, return the file name passed in.
    return pszFileName;
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return CCString::create(fullPathForFilename(pszRelativePath))->getCString();
}


const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	std::string relativeFile = pszRelativeFile;
	CCString *pRet = CCString::create("");
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += getNewFilename(pszFilename);
	return pRet->m_sString.c_str();
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
        std::string fullPath = fullPathForFilename(pszFileName);
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
		msg.append(pszFileName).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}
	return pData;

}

void CCFileUtils::setResourceDirectory(const char* pszResourceDirectory)
{
    if (pszResourceDirectory == NULL) return;
    m_obDirectory = pszResourceDirectory;
    std::vector<std::string> searchPaths = this->getSearchPaths();;
    searchPaths.insert(searchPaths.begin(), pszResourceDirectory);
    this->setSearchPaths(searchPaths);
}

void CCFileUtils::setSearchPaths(const std::vector<std::string>& searchPaths)
{
    bool bExistDefaultRootPath = false;

    m_searchPathArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); ++iter)
    {
        std::string strPrefix;
        std::string path;
        if ((*iter)[0] != '/')
        { // Not an absolute path
            if (iter->find(m_strDefaultResRootPath) != 0)
            { // The path contains no default resource root path, insert the root path.
                strPrefix = m_strDefaultResRootPath;
            }
        }
        path = strPrefix+(*iter);
        if (path.length() > 0 && path[path.length()-1] != '/')
        {
            path += "/";
        }
        if (!bExistDefaultRootPath && path == m_strDefaultResRootPath)
        {
            bExistDefaultRootPath = true;
        }
        m_searchPathArray.push_back(path);
    }

    if (!bExistDefaultRootPath)
    {
        //CCLOG("Default root path doesn't exist, adding it.");
        m_searchPathArray.push_back(m_strDefaultResRootPath);
    }
}

string CCFileUtils::getWriteablePath()
{
	//return current resource path
  return m_strDefaultResRootPath;
}

NS_CC_END
