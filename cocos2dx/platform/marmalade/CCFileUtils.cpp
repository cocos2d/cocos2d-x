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

static char s_pszResourcePath[S3E_FILE_MAX_PATH] = {0};

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
	// TODO HOW ARE WE SUPPOSED TO WRITE BACK TO THE "ignore" REFERENCE?
	IwAssert(GAME, pszRelativePath);

	bool bFileExist = true;
	const char* resDir = m_obDirectory.c_str();
	CCString * pRet = new CCString();

	pRet->autorelease();
	if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
	{
		pRet->m_sString = resDir;
		pRet->m_sString += pszRelativePath;
	}
	else if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
	{
		char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
		pRet->m_sString = szDriver;
		pRet->m_sString += resDir;
		pRet->m_sString += pszRelativePath;
	}
	else
	{
		pRet->m_sString = s_pszResourcePath;
		pRet->m_sString += resDir;
		pRet->m_sString += pszRelativePath;
	}

	bool exists = s3eFileCheckExists(pRet->getCString()) == S3E_TRUE;
	if (!exists)
	{
		if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
		{
			pRet->m_sString = pszRelativePath;
		}
		else if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
		{
			char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
			pRet->m_sString = szDriver;
			pRet->m_sString += pszRelativePath;
		}
		else
		{
			pRet->m_sString = s_pszResourcePath;
			pRet->m_sString += pszRelativePath;
		}

		bFileExist = s3eFileCheckExists(pRet->getCString()) == S3E_TRUE;
	}

	if (!bFileExist)
	{
		pRet->m_sString = pszRelativePath;
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

std::string CCFileUtils::getWriteablePath()
{
	return std::string("ram://");
}

NS_CC_END; 

