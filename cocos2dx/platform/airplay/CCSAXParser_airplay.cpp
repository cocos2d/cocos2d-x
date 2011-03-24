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
void CCSAXParser::init(const char *pszEncoding)
{
	s_pParser = XML_ParserCreate(reinterpret_cast<const XML_Char*>(pszEncoding));
	XML_SetUserData(s_pParser, this);
	XML_SetElementHandler(s_pParser, startElement, endElement);
	XML_SetCharacterDataHandler(s_pParser, textHandler);

}
void CCSAXParser::parse(const char *pszFile)
{

		s3eFile* file = s3eFileOpen(pszFile, "r");
		IwAssertMsg(GAME, file, ("Open file %s Failed. s3eFileError Code : %i", pszFile, s3eFileGetError()));
		s3eFileSeek(file, 0, S3E_FILESEEK_END);
		int	size = s3eFileTell(file);
		s3eFileSeek(file, 0,  S3E_FILESEEK_SET);
		char* buf = new char[size];
		int done =0;
		int len = (int)s3eFileRead(buf, 1, size, file);
		if (XML_Parse(s_pParser, buf, len, 1) == XML_STATUS_ERROR)
		{
			CCLog("GAME: cocos2d: plist err: %s at line %d", XML_ErrorString(XML_GetErrorCode(s_pParser)), XML_GetCurrentLineNumber(s_pParser));
		}
		s3eFileClose(file);
		delete []buf;

}
void CCSAXParser::startElement(void *ctx, const char *name, const char **atts)
{
	((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (XML_Char)name, atts);
}

void CCSAXParser::endElement(void *ctx, const char *name)
{
	((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (XML_Char)name);
}
void CCSAXParser::textHandler(void *ctx, const char *name, int len)
{
	((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (XML_Char)name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
	m_pDelegator = pDelegator;
}

NS_CC_END;


