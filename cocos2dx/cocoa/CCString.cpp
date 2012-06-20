#include "CCString.h"
#include "platform/CCFileUtils.h"
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>

NS_CC_BEGIN

#define kMaxStringLen (1024*100)

CCString::CCString()
    :m_sString("")
{}

CCString::CCString(const char * str)
    :m_sString(str)
{}

CCString::CCString(const std::string& str)
    :m_sString(str)
{}

CCString::CCString(const CCString& str)
    :m_sString(str.getCString())
{}

CCString::~CCString()
{ 
    m_sString.clear();
}

CCString& CCString::operator= (const CCString& other)
{
    m_sString = other.m_sString;
    return *this;
}

bool CCString::initWithFormatAndValist(const char* format, va_list ap)
{
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        m_sString = pBuf;
        free(pBuf);
        bRet = true;
    }
    return bRet;
}

bool CCString::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    m_sString.clear();

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
    return atoi(m_sString.c_str());
}

unsigned int CCString::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(m_sString.c_str());
}

float CCString::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(m_sString.c_str());
}

double CCString::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(m_sString.c_str());
}

bool CCString::boolValue() const
{
    if (length() == 0)
    {
        return false;
    }

    if (0 == strcmp(m_sString.c_str(), "0") || 0 == strcmp(m_sString.c_str(), "false"))
    {
        return false;
    }
    return true;
}

const char* CCString::getCString() const
{
    return m_sString.c_str();
}

unsigned int CCString::length() const
{
    return m_sString.length();
}

int CCString::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}

CCObject* CCString::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCString should not be inherited.");
    CCString* pStr = new CCString(m_sString.c_str());
    return pStr;
}

bool CCString::isEqual(const CCObject* pObject)
{
    bool bRet = false;
    const CCString* pStr = dynamic_cast<const CCString*>(pObject);
    if (pStr != NULL)
    {
        if (0 == m_sString.compare(pStr->m_sString))
        {
            bRet = true;
        }
    }
    return bRet;
}

CCString* CCString::stringWithCString(const char* pStr)
{
    return CCString::create(pStr);
}

CCString* CCString::create(const std::string& str)
{
    CCString* pRet = new CCString(str);
    pRet->autorelease();
    return pRet;
}

CCString* CCString::stringWithString(const std::string& pStr)
{
    CCString* pRet = new CCString(pStr);
    pRet->autorelease();
    return pRet;
}

CCString* CCString::stringWithData(const unsigned char* pData, unsigned long nLen)
{
    return CCString::createWithData(pData, nLen);
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

CCString* CCString::stringWithFormat(const char* format, ...)
{
    CCString* pRet = CCString::create("");
    va_list ap;
    va_start(ap, format);
    pRet->initWithFormatAndValist(format, ap);
    va_end(ap);

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

CCString* CCString::stringWithContentsOfFile(const char* pszFileName)
{
    return CCString::createWithContentsOfFile(pszFileName);
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

NS_CC_END
