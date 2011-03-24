#ifndef __CCSAXPARSER_H__
#define __CCSAXPARSER_H__

NS_CC_BEGIN;

class CCSAXDelegator
{
public:
	virtual void startElement(const char *name, const char **atts) = 0;
	virtual void endElement(const char *name) = 0;
	virtual void textHandler(const char *s, int len) = 0;
};

class CCSAXParser
{
	CCSAXDelegator*	m_pDelegator;
public:

	CCSAXParser();
	~CCSAXParser(void);

	void init(const char *pszEncoding);
	void parse(const char *pszFile);
	void setDelegator(CCSAXDelegator* pDelegator);

	static void startElement(void *ctx, const char *name, const char **atts);
	static void endElement(void *ctx, const char *name);
	static void textHandler(void *ctx, const char *name, int len);
};
NS_CC_END;

#endif //__CCSAXPARSER_H__