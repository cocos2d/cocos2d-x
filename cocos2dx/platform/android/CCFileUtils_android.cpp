/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCString.h"
#include "CCFileUtils_android.h"
#include "CCCocos2dDefine.h"
#include "support/file_support/FileData.h"
#include "support/zip_support/unzip.h"

namespace cocos2d {

void plist_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
void plist_endElement(void *ctx, const xmlChar *name);
void plist_characters(void *ctx, const xmlChar *ch, int len);

typedef enum 
{
	SAX_NONE = 0,
	SAX_KEY,
	SAX_DICT,
	SAX_INT,
	SAX_REAL,
	SAX_STRING
}CCSAXState;

class CCDictMaker
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
	CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFile(const char *pFileName)
	{
		FileData data;
        unsigned long size = 0;
        char *pBuffer = (char *) data.getFileData(pFileName, "r", &size);

        if (! pBuffer)
        {
            return NULL;
        }
        
		/*
		* this initialize the library and check potential ABI mismatches
		* between the version it was compiled for and the actual shared
		* library used.
		*/
		LIBXML_TEST_VERSION
		xmlSAXHandler saxHandler;
		memset( &saxHandler, 0, sizeof(saxHandler) );
		// Using xmlSAXVersion( &saxHandler, 2 ) generate crash as it sets plenty of other pointers...
		saxHandler.initialized = XML_SAX2_MAGIC;  // so we do this to force parsing as SAX2.
 		saxHandler.startElement = &plist_startElement;
 		saxHandler.endElement = &plist_endElement;
 		saxHandler.characters = &plist_characters;

		int result = xmlSAXUserParseMemory( &saxHandler, this, pBuffer, size );
		if ( result != 0 )
		{
			return NULL;
		}
		/*
		* Cleanup function for the XML library.
		*/
		xmlCleanupParser();
		/*
		* this is to debug memory for regression tests
		*/
		xmlMemoryDump();
		return m_pRootDict;
	}
};
void plist_startElement(void *ctx, const xmlChar *name, const xmlChar **atts)
{
	CCDictMaker *pMaker = (CCDictMaker*)(ctx);
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
void plist_endElement(void *ctx, const xmlChar *name)
{
	CCDictMaker * pMaker = (CCDictMaker*)(ctx);
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
void plist_characters(void *ctx, const xmlChar *ch, int len)
{
 	CCDictMaker * pMaker = (CCDictMaker*)(ctx);
	if (pMaker->m_tState == SAX_NONE)
	{
		return;
	}
 	CCString *pText = new CCString();
	pText->m_sString = std::string((char*)ch,0,len);

 	switch(pMaker->m_tState)
 	{
 	case SAX_KEY:
 		pMaker->m_sCurKey = pText->m_sString;
 		break;
 	case SAX_INT:
 	case SAX_REAL:
 	case SAX_STRING:
 		{
 			CCAssert(!pMaker->m_sCurKey.empty(), "not found key : <integet/real>");
 			pMaker->m_pCurDict->setObject(pText, pMaker->m_sCurKey);
 			break;
 		}
 	}
	pText->release();
}

// record the resource path

string CCFileUtils::m_sRelativePath = "";
string CCFileUtils::m_sResourcePath = "";
	
void CCFileUtils::setRelativePath(const char* pszRelativePath)
{
	CCAssert(pszRelativePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
	
	if (! pszRelativePath)
	{
		return;
	}
	
	m_sRelativePath = pszRelativePath;
	
	// if the path is not ended with '/', append it
	if (m_sRelativePath.find("/") != (strlen(m_sRelativePath.c_str()) - 1))
	{
		m_sRelativePath += "/";
	}
}

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
    CCAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

    m_sResourcePath = pszResourcePath;
}

const char* CCFileUtils::getResourcePath()
{
	return m_sResourcePath.c_str();
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	return pszRelativePath;
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	//std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
	std::string relativeFile = pszRelativeFile;
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
	string fullPath = m_sRelativePath + pszFileName;
	return FileUtils::getFileDataFromZip(m_sResourcePath.c_str(), fullPath.c_str(), pSize);
}

}//namespace   cocos2d 
