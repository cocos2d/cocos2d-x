#include "CCSAXParser_airplay.h"
#include "IwUtil.h"
NS_CC_BEGIN;

CCSAXParser::CCSAXParser()
{
	m_pDelegator = NULL;

}
CCSAXParser::~CCSAXParser(void)
{
	if(m_parser)
	{
		XML_ParserFree(m_parser);
	}
}
void CCSAXParser::init(const char *pszEncoding)
{
	m_parser = XML_ParserCreate(reinterpret_cast<const XML_Char*>(pszEncoding));
	XML_SetUserData(m_parser, this);
	XML_SetElementHandler(m_parser, startElement, endElement);
	XML_SetCharacterDataHandler(m_parser, textHandler);

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
		if (XML_Parse(m_parser, buf, len, 1) == XML_STATUS_ERROR)
		{
			CCLog("GAME: cocos2d: plist err: %s at line %d", XML_ErrorString(XML_GetErrorCode(m_parser)), XML_GetCurrentLineNumber(m_parser));
		}
		s3eFileClose(file);
		delete []buf;

}
void CCSAXParser::startElement(void *ctx, const XML_Char *name, const XML_Char **atts)
{
	((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, name, atts);
}

void CCSAXParser::endElement(void *ctx, const XML_Char *name)
{
	((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, name);
}
void CCSAXParser::textHandler(void *ctx, const XML_Char *name, int len)
{
	((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
	m_pDelegator = pDelegator;
}
NS_CC_END;


