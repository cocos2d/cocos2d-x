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
#include <tg3.h>
#include "CCFileUtils.h"
#include "Cocos2dDefine.h"

typedef std::pair<std::string, void*> Pair;
typedef enum 
{
	SAX_NONE = 0,
	SAX_KEY,
	SAX_DICT,
	SAX_INT,
	SAX_REAL
}CCSAXState;

class CCDictMaker
{
public:
	CCDictionary *m_pRootDict;
	CCDictionary *m_pCurDict;
	std::stack<CCDictionary*> m_tDictStack;
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
	CCDictionary *dictionaryWithContentsOfFile(const char *pFileName)
	{
		FILE *fp;
		if( !(fp = fopen(pFileName, "r")) )
		{
			return NULL;
		}
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		char *buffer = new char[size];
		fread(buffer,sizeof(char),size,fp);
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
		saxHandler.startElement = &startElement;
		saxHandler.endElement = &endElement;
		saxHandler.characters = &characters;

		int result = xmlSAXUserParseMemory( &saxHandler, this, buffer, size );
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
		delete []buffer;
		return m_pRootDict;
	}
};
void startElement(void *ctx, const xmlChar *name, const xmlChar **atts)
{
	CCDictMaker *pMaker = static_cast<CCDictMaker*>(ctx);
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		CCDictionary *pNewDict = new CCDictionary();
		if(! pMaker->m_pRootDict)
		{
			pMaker->m_pRootDict = pNewDict;
		}
		else
		{
			NSAssert(pMaker->m_pCurDict && !pMaker->m_sCurKey.empty(), "");
			pMaker->m_pCurDict->insert( Pair(pMaker->m_sCurKey, pNewDict) );
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
	else
	{
		pMaker->m_tState = SAX_NONE;
	}
}
void endElement(void *ctx, const xmlChar *name)
{
	CCDictMaker * pMaker = static_cast<CCDictMaker*>(ctx);
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		pMaker->m_tDictStack.pop();
		if ( !pMaker->m_tDictStack.empty() )
		{
			pMaker->m_pCurDict = static_cast<CCDictionary*>(pMaker->m_tDictStack.top());
		}
	}
}
void characters(void *ctx, const xmlChar *ch, int len)
{
	CCDictMaker * pMaker = static_cast<CCDictMaker*>(ctx);
	std::string *pText = new std::string((char*)ch,0,len);
	switch(pMaker->m_tState)
	{
	case SAX_KEY:
		pMaker->m_sCurKey = *pText;
		break;
	case SAX_INT:
	case SAX_REAL:
		{
			NSAssert(!pMaker->m_sCurKey.empty(), "not found key : <integet/real>");
			pMaker->m_pCurDict->insert( Pair(pMaker->m_sCurKey, pText) );
			break;
		}
	}
}
char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	// do not convert an absolute path (starting with '/')
	if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
	{
		return (char*)pszRelativePath;
	}

	// get the user data path and append relativepath to it
	const TUChar *pszTmp = EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_USER_DATA);
	char *pszUserPath = new char[TUString::StrLen(pszTmp) + 1];
	TUString::StrUnicodeToStrUtf8((Char*)pszUserPath, pszTmp);
	char *pszRet;

	INT32 nLen = strlen(pszRelativePath) + strlen(pszUserPath) + 1;
	pszRet = new char[nLen];
	memset(pszRet, 0, nLen);
	strncat(pszRet, pszUserPath, strlen(pszUserPath));
	strncat(pszRet, pszRelativePath, strlen(pszRelativePath));

	return pszRet;
}

CCDictionary *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
{
	CCDictMaker tMaker;
	return tMaker.dictionaryWithContentsOfFile(pFileName);
}
