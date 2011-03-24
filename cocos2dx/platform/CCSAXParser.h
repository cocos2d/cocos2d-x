#ifndef __CCSAXPARSER_H__
#define __CCSAXPARSER_H__

#include "CCPlatformConfig.h"
#include "CCCommon.h"

NS_CC_BEGIN;

// libxml2 on most platforms are using "unsigned char" as type of string, while on airplay sdk using "char"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)   || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || \
	(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
typedef unsigned char CC_XML_CHAR;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
typedef char CC_XML_CHAR
#else
#error
#endif

class CCSAXDelegator
{
public:
	virtual void startElement(void *ctx, const char *name, const char **atts) = 0;
	virtual void endElement(void *ctx, const char *name) = 0;
	virtual void textHandler(void *ctx, const char *s, int len) = 0;
};

class CCSAXParser
{
	CCSAXDelegator*	m_pDelegator;
public:

	CCSAXParser();
	~CCSAXParser(void);

	bool init(const char *pszEncoding);
	bool parse(const char *pszFile);
	void setDelegator(CCSAXDelegator* pDelegator);

	static void startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts);
	static void endElement(void *ctx, const CC_XML_CHAR *name);
	static void textHandler(void *ctx, const CC_XML_CHAR *name, int len);
};
NS_CC_END;

#endif //__CCSAXPARSER_H__