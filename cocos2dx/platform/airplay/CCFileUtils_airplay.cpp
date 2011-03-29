/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 
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

#include "CCFileUtils.h"
#include "string.h"
#include "stack"
#include "expat.h"
#include "CCString.h"

#include "support/zip_support/unzip.h"
#include "../CCSAXParser.h"
#include "CCApplication.h"
#include "CCMutableArray.h"

NS_CC_BEGIN;

typedef enum 
{
	SAX_NONE = 0,
	SAX_KEY,
	SAX_DICT,
	SAX_INT,
	SAX_REAL,
	SAX_STRING
}CCSAXState;


class CCDictMaker : public CCSAXDelegator
{
public:
	CCDictionary<std::string, CCObject*> *m_pRootDict;
	CCDictionary<std::string, CCObject*> *m_pCurDict;
	std::stack<CCDictionary<std::string, CCObject*>*> m_tDictStack;
	std::string m_sCurKey;///< parsed key
	CCSAXState m_tState;

public:
	CCDictMaker()
	{
		m_pRootDict = NULL;
		m_pCurDict = NULL;
		m_tState = SAX_NONE;
	}
	~CCDictMaker()
	{

	}
	CCDictionary<std::string, CCObject*> *getDict()
	{
		return m_pRootDict;
	}
	CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFile(const char *pFileName)
	{
		CCSAXParser parser;
		parser.init(NULL);
		parser.setDelegator(this);
		parser.parse(pFileName);
		return m_pRootDict;
	}

void startElement(void *ctx, const XML_Char *name, const XML_Char **atts)
{
	CCDictMaker *pMaker = this;
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		CCDictionary<std::string, CCObject*> *pNewDict = new CCDictionary<std::string, CCObject*>();
		if(! pMaker->m_pRootDict)
		{
			pMaker->m_pRootDict = pNewDict;
			pNewDict->autorelease();
		}
		else
		{
			CCAssert(pMaker->m_pCurDict && !pMaker->m_sCurKey.empty(), "");
			pMaker->m_pCurDict->setObject(pNewDict, pMaker->m_sCurKey);
			pNewDict->release();
			pMaker->m_sCurKey.clear();
		}
		pMaker->m_pCurDict = pNewDict;
		pMaker->m_tDictStack.push(pMaker->m_pCurDict);
		pMaker->m_tState = SAX_DICT;
	}
	else if(sName == "key")
	{
		pMaker->m_tState = SAX_KEY;
	}
	else if(sName == "integer")
	{
		pMaker->m_tState = SAX_INT;
	}
	else if(sName == "real")
	{
		pMaker->m_tState = SAX_REAL;
	}
	else if(sName == "string")
	{
		pMaker->m_tState = SAX_STRING;
	}
	else
	{
		pMaker->m_tState = SAX_NONE;
	}	
}
void endElement(void *ctx, const XML_Char *name)
{
	CCDictMaker * pMaker = this;
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		pMaker->m_tDictStack.pop();
		if ( !pMaker->m_tDictStack.empty() )
		{
			pMaker->m_pCurDict = (CCDictionary<std::string, CCObject*>*)(pMaker->m_tDictStack.top());
		}
	}
	pMaker->m_tState = SAX_NONE;
}

void textHandler(void *ctx, const XML_Char *ch, int len)
{
 	CCDictMaker * pMaker = this;
	if (pMaker->m_tState == SAX_NONE)
	{
		return;
	}
 	CCString *pText = new CCString();
	pText->m_sString = std::string((char*)ch,0,len);

 	switch(pMaker->m_tState)
 	{
 	case SAX_KEY:
		{
			pMaker->m_sCurKey = pText->m_sString;
		}
 		break;
 	case SAX_INT:
 	case SAX_REAL:
 		{
 			CCAssert(!pMaker->m_sCurKey.empty(), "not found real : <integet/real>");
 			pMaker->m_pCurDict->setObject(pText, pMaker->m_sCurKey);
 			break;
 		}
 	case SAX_STRING:
 		{
 			CCAssert(!pMaker->m_sCurKey.empty(), "not found string");
 			pMaker->m_pCurDict->setObject(pText, pMaker->m_sCurKey);
 			break;
 		}
 	}
	pText->release();
}
};


static char s_pszResourcePath[S3E_FILE_MAX_PATH] = {0};

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{

	IwAssert(GAME, pszRelativePath);

	CCString * pRet = new CCString();
    pRet->autorelease();
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

CCDictionary<std::string, CCObject*> *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
{
	CCDictMaker tMaker;
	return tMaker.dictionaryWithContentsOfFile(pFileName);
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
	IW_CALLSTACK("CCFileUtils::getFileData");

	s3eFile* pFile = s3eFileOpen(pszFileName, pszMode);
	

	IwAssertMsg(GAME, pFile, ("Open file %s Failed. s3eFileError Code : %i", pszFileName, s3eFileGetError()));
	
	int32 fileSize = s3eFileGetSize(pFile);
	*pSize=fileSize;

	static int32* pDataToBeReadBinary;

	pDataToBeReadBinary = (int32*)s3eMallocBase(fileSize);
	memset(pDataToBeReadBinary, 0, fileSize);
	s3eFileRead(pDataToBeReadBinary, fileSize, 1, pFile);
	s3eFileClose(pFile);
	
	return (unsigned char*)pDataToBeReadBinary;
}

std::string& CCFileUtils::ccRemoveHDSuffixFromFile(std::string& path)
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if( CC_CONTENT_SCALE_FACTOR() == 2 )
    {
        std::string::size_type pos = path.rfind("/") + 1; // the begin index of last part of path

        std::string::size_type suffixPos = path.rfind(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
        if (std::string::npos != suffixPos && suffixPos > pos)
        {
            CCLog("cocos2d: FilePath(%s) contains suffix(%s), remove it.", path.c_str(),
                CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            path.replace(suffixPos, strlen(CC_RETINA_DISPLAY_FILENAME_SUFFIX), "");
        }
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return path;
}

NS_CC_END; 

