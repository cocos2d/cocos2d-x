/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org  http://cocos2d-x.org
 Copyright (c) 2010 Максим Аксенов
 
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

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCSAXParser.h"
#include "cocoa/CCDictionary.h"
#include "CCFileUtils.h"

NS_CC_BEGIN

CCSAXParser::CCSAXParser()
{
    m_pDelegator = NULL;
}

CCSAXParser::~CCSAXParser(void)
{
}

bool CCSAXParser::init(const char *pszEncoding)
{
    CC_UNUSED_PARAM(pszEncoding);
    // nothing to do
    return true;
}

bool CCSAXParser::parse(const char* pXMLData, unsigned int uDataLength)
{
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
    
    int result = xmlSAXUserParseMemory( &saxHandler, this, pXMLData, uDataLength );
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
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
    xmlMemoryDump();
#endif
    
    return true;
}

bool CCSAXParser::parse(const char *pszFile)
{
    bool bRet = false;
    unsigned long size = 0;
    char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(pszFile, "rt", &size);
    if (pBuffer != NULL && size > 0)
    {
        bRet = parse(pBuffer, size);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
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

NS_CC_END


