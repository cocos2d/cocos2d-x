#include "CCString.h"
#include "platform/CCFileUtils.h"
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>

NS_CC_BEGIN

#define kMaxStringLen (1024*100)

CCString::CCString()
    :_string("")
{}

CCString::CCString(const char * str)
    :_string(str)
{}

CCString::CCString(const std::string& str)
    :_string(str)
{}

CCString::CCString(const CCString& str)
    :_string(str.getCString())
{}

CCString::~CCString()
{ 
    _string.clear();
}

CCString& CCString::operator= (const CCString& other)
{
    _string = other._string;
    return *this;
}

bool CCString::initWithFormatAndValist(const char* format, va_list ap)
{
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        _string = pBuf;
        free(pBuf);
        bRet = true;
    }
    return bRet;
}

bool CCString::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    _string.clear();

    va_list ap;
    va_start(ap, format);

    bRet = initWithFormatAndValist(format, ap);

    va_end(ap);

    return bRet;
}

int CCString::intValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return atoi(_string.c_str());
}

unsigned int CCString::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(_string.c_str());
}

float CCString::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(_string.c_str());
}

double CCString::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(_string.c_str());
}

bool CCString::boolValue() const
{
    if (length() == 0)
    {
        return false;
    }

    if (0 == strcmp(_string.c_str(), "0") || 0 == strcmp(_string.c_str(), "false"))
    {
        return false;
    }
    return true;
}

const char* CCString::getCString() const
{
    return _string.c_str();
}

unsigned int CCString::length() const
{
    return _string.length();
}

int CCString::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}

CCObject* CCString::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCString should not be inherited.");
    CCString* pStr = new CCString(_string.c_str());
    return pStr;
}

bool CCString::isEqual(const CCObject* pObject)
{
    bool bRet = false;
    const CCString* pStr = dynamic_cast<const CCString*>(pObject);
    if (pStr != NULL)
    {
        if (0 == _string.compare(pStr->_string))
        {
            bRet = true;
        }
    }
    return bRet;
}

CCString* CCString::create(const std::string& str)
{
    CCString* pRet = new CCString(str);
    pRet->autorelease();
    return pRet;
}

CCString* CCString::createWithData(const unsigned char* pData, unsigned long nLen)
{
    CCString* pRet = NULL;
    if (pData != NULL)
    {
        char* pStr = (char*)malloc(nLen+1);
        if (pStr != NULL)
        {
            pStr[nLen] = '\0';
            if (nLen > 0)
            {
                memcpy(pStr, pData, nLen);
            }
            
            pRet = CCString::create(pStr);
            free(pStr);
        }
    }
    return pRet;
}

CCString* CCString::createWithFormat(const char* format, ...)
{
    CCString* pRet = CCString::create("");
    va_list ap;
    va_start(ap, format);
    pRet->initWithFormatAndValist(format, ap);
    va_end(ap);

    return pRet;
}

CCString* CCString::createWithContentsOfFile(const char* pszFileName)
{
    unsigned long size = 0;
    unsigned char* pData = 0;
    CCString* pRet = NULL;
    pData = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, "rb", &size);
    pRet = CCString::createWithData(pData, size);
    CC_SAFE_DELETE_ARRAY(pData);
    return pRet;
}

void CCString::acceptVisitor(CCDataVisitor &visitor)
{
    visitor.visit(this);
}

NS_CC_END
