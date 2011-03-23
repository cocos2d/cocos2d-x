#ifndef __CCSAXPARSER_AIRPLAY_H__
#define __CCSAXPARSER_AIRPLAY_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY) //for ios proj

#include "expat.h"
#include "CCMutableDictionary.h"

NS_CC_BEGIN;

class CCSAXDelegator
{
public:
	virtual void startElement(void *ctx, const XML_Char *name, const XML_Char **atts) = 0;
	virtual void endElement(void *ctx,const XML_Char *name) = 0;
	virtual void textHandler(void *ctx,const XML_Char *s, int len) = 0;
};

class CCSAXParser
{
	XML_Parser			m_parser;
	CCSAXDelegator*	m_pDelegator;
public:

	CCSAXParser();
	~CCSAXParser(void);

	void init(const char *pszEncoding);
	void parse(const char *pszFile);
	void setDelegator(CCSAXDelegator* pDelegator);

	static void startElement(void *ctx, const XML_Char *name, const XML_Char **atts);
	static void endElement(void *ctx, const XML_Char *name);
	static void textHandler(void *ctx, const XML_Char *name, int len);
};
NS_CC_END;
#endif //CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY
#endif //__CCSAXPARSER_AIRPLAY_H__