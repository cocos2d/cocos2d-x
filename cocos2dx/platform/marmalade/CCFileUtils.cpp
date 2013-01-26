/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck
 
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
#include "CCFileUtils.h"
#include "CCFileUtilsCommon_cpp.h"
#include "string.h"
#include "stack"
#include "CCString.h"

#include "CCApplication.h"

#include "IwDebug.h" // for CCLog


NS_CC_BEGIN;


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
    s_fullPathCache.clear();
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string ret = "";

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

std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    // TODO HOW ARE WE SUPPOSED TO WRITE BACK TO THE "ignore" REFERENCE?
	IwAssert(GAME, pszFileName);
    
    // Return directly if it's an absolute path.
    if (pszFileName[0] == '/')
    {
        return pszFileName;
    }
    
    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = s_fullPathCache.find(pszFileName);
    if (cacheIter != s_fullPathCache.end()) {
        CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }

    std::string newFileName = getNewFilename(pszFileName);
    std::string fullpath;
    
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
            if (s3eFileCheckExists(fullpath.c_str()) == S3E_TRUE)
            {
                // Adding the full path to cache if the file was found.
                s_fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
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
	IW_CALLSTACK("CCFileUtils::getFileData");

	s3eFile* pFile = s3eFileOpen(pszFileName, pszMode);
	
	if (! pFile && isPopupNotify())
	{    
		IwAssertMsg(GAME, pFile, ("Open file %s Failed. s3eFileError Code : %i", pszFileName, s3eFileGetError()));
	}
	if (! pFile) 
	{
		*pSize = 0;
		return 0;
	}
	int32 fileSize = s3eFileGetSize(pFile);
	*pSize=fileSize;

	static int32* pDataToBeReadBinary;

	pDataToBeReadBinary = (int32*)s3eMallocBase(fileSize);
	memset(pDataToBeReadBinary, 0, fileSize);
	s3eFileRead(pDataToBeReadBinary, fileSize, 1, pFile);
	s3eFileClose(pFile);
	
	return (unsigned char*)pDataToBeReadBinary;
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

std::string CCFileUtils::getWriteablePath()
{
	return std::string("ram://");
}

NS_CC_END; 

