#include "CCSAXParser.h"
#include "CCMutableDictionary.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCLibxml2.h"
#include "CCFileUtils.h"

NS_CC_BEGIN;

CCSAXParser::CCSAXParser()
{
	m_pDelegator = NULL;

}

CCSAXParser::~CCSAXParser(void)
{
}

bool CCSAXParser::init(const char *pszEncoding)
{
	// nothing to do
	return true;
}

bool CCSAXParser::parse(const char *pszFile)
{
	FileData data;
	unsigned long size = 0;
	char *pBuffer = (char*) data.getFileData(pszFile, "r", &size);
	
	if (!pBuffer)
	{
		return false;
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
	saxHandler.startElement = &CCSAXParser::startElement;
	saxHandler.endElement = &CCSAXParser::endElement;
	saxHandler.characters = &CCSAXParser::textHandler;
	
	int result = xmlSAXUserParseMemory( &saxHandler, this, pBuffer, size );
	if ( result != 0 )
	{
		return false;
	}
	/*
	 * Cleanup function for the XML library.
	 */
	xmlCleanupParser();
	/*
	 * this is to debug memory for regression tests
	 */
	xmlMemoryDump();
	
	return true;
}

void CCSAXParser::startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts)
{
	((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (char*)name, (const char**)atts);
}

void CCSAXParser::endElement(void *ctx, const CC_XML_CHAR *name)
{
	((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (char*)name);
}
void CCSAXParser::textHandler(void *ctx, const CC_XML_CHAR *name, int len)
{
	((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (char*)name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
	m_pDelegator = pDelegator;
}

NS_CC_END;


