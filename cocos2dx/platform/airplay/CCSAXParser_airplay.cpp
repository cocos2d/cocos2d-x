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

#include "CCSAXParser.h"
#include "expat.h"
#include "CCMutableDictionary.h"
#include "IwUtil.h"

NS_CC_BEGIN;

static XML_Parser s_pParser = NULL;

CCSAXParser::CCSAXParser()
{
	s_pParser = NULL;
	m_pDelegator = NULL;

}
CCSAXParser::~CCSAXParser(void)
{
	if(s_pParser)
	{
		XML_ParserFree(s_pParser);
		s_pParser = NULL;
	}
}
bool CCSAXParser::init(const char *pszEncoding)
{
	s_pParser = XML_ParserCreate(reinterpret_cast<const XML_Char*>(pszEncoding));
	XML_SetUserData(s_pParser, this);
	XML_SetElementHandler(s_pParser, startElement, endElement);
	XML_SetCharacterDataHandler(s_pParser, textHandler);
	return true;
}
bool CCSAXParser::parse(const char *pszFile)
{
	bool bRet = false;
	char* buf = NULL;
	s3eFile* file = NULL;
	
	do
	{
		file = s3eFileOpen(pszFile, "r");
		
		if (!file)
		{
			IwAssertMsg(GAME, file, ("Open file %s Failed. s3eFileError Code : %i", pszFile, s3eFileGetError()));
			break;
		}
		
		s3eFileSeek(file, 0, S3E_FILESEEK_END);
		int	size = s3eFileTell(file);
		s3eFileSeek(file, 0,  S3E_FILESEEK_SET);
		buf = new char[size];
		int done =0;
		int len = (int)s3eFileRead(buf, 1, size, file);
		if (XML_Parse(s_pParser, buf, len, 1) == XML_STATUS_ERROR)
		{
			CCLog("GAME: cocos2d: plist err: %s at line %d", XML_ErrorString(XML_GetErrorCode(s_pParser)), XML_GetCurrentLineNumber(s_pParser));
			break;
		}
		
		bRet = true;
		
	} while(0);
	
	// cleanup
	if (file)
	{
		s3eFileClose(file);
	}
	if (buf)
	{
		delete []buf;
	}
	
	return bRet;

}
void CCSAXParser::startElement(void *ctx, const char *name, const char **atts)
{
	((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (const char*)name, (const char**)atts);
}

void CCSAXParser::endElement(void *ctx, const char *name)
{
	((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (const char*)name);
}
void CCSAXParser::textHandler(void *ctx, const char *name, int len)
{
	((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (const char*)name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
	m_pDelegator = pDelegator;
}

NS_CC_END;


