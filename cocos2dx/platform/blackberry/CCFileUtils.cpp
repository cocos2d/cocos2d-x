/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

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

#define __CC_PLATFORM_FILEUTILS_CPP__
#include "platform/CCFileUtilsCommon_cpp.h"
#include "CCApplication.h"
#include <unistd.h>

NS_CC_BEGIN;

#define  MAX_PATH 256

static CCFileUtils *s_pFileUtils = 0;

CCFileUtils *CCFileUtils::sharedFileUtils()
{
	if (!s_pFileUtils) {
		s_pFileUtils = new CCFileUtils();
		s_pFileUtils->init();
	}

	return s_pFileUtils;
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

bool CCFileUtils::init()
{
    m_pSearchPathArray = new CCArray();
    m_pSearchPathArray->addObject(CCString::create(""));

    m_pSearchResolutionsOrderArray = new CCArray();
    m_pSearchResolutionsOrderArray->addObject(CCString::create(""));

    return true;
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
                if (access(fullpath.c_str(), F_OK) != -1)
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
	unsigned char *buffer = 0;
	std::string full_path(pszFileName);

	if (!pszFileName || !pszMode)
	{
		return 0;
	}

	do
	{
		// read from other path than user set it
		FILE *fp = fopen(full_path.c_str(), pszMode);
		CC_BREAK_IF(!fp);

		unsigned long size;
		fseek(fp,0,SEEK_END);
		size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		buffer = new unsigned char[size];
		size = fread(buffer, sizeof(unsigned char), size, fp);
		fclose(fp);

		if (pSize)
		{
			*pSize = size;
		}
	} while (0);

	if (!buffer && isPopupNotify())
	{
		std::string title = "Notification";
		std::string msg = "Get data from file(";
		msg.append(full_path.c_str()).append(") failed!");
		CCMessageBox(msg.c_str(), title.c_str());
	}

	return buffer;
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
