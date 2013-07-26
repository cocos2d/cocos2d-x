#include "CCString.h"
#include "platform/CCFileUtils.h"
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>
#include "CCArray.h"

NS_CC_BEGIN

#define kMaxStringLen (1024*100)

String::String()
    :_string("")
{}

String::String(const char * str)
    :_string(str)
{}

String::String(const std::string& str)
    :_string(str)
{}

String::String(const String& str)
    :_string(str.getCString())
{}

String::~String()
{ 
    _string.clear();
}

String& String::operator= (const String& other)
{
    _string = other._string;
    return *this;
}

bool String::initWithFormatAndValist(const char* format, va_list ap)
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

bool String::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    _string.clear();

    va_list ap;
    va_start(ap, format);

    bRet = initWithFormatAndValist(format, ap);

    va_end(ap);

    return bRet;
}

int String::intValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return atoi(_string.c_str());
}

unsigned int String::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(_string.c_str());
}

float String::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(_string.c_str());
}

double String::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(_string.c_str());
}

bool String::boolValue() const
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

const char* String::getCString() const
{
    return _string.c_str();
}

unsigned int String::length() const
{
    return _string.length();
}

int String::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}

void String::append(const std::string& str)
{
    _string.append(str);
}

void String::appendWithFormat(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        _string.append(pBuf);
        free(pBuf);
    }
    
    va_end(ap);
    
}

Array* String::componentsSeparatedByString(const char *delimiter)
{
    Array* result = Array::create();
    
    int cutAt;
    while( (cutAt = _string.find_first_of(delimiter)) != _string.npos )
    {
        if(cutAt > 0)
        {
            result->addObject(String::create(_string.substr(0, cutAt)));
        }
        _string = _string.substr(cutAt + 1);
    }
    
    if(_string.length() > 0)
    {
        result->addObject(String::create(_string));
    }
    
    return result;
}

bool String::isEqual(const Object* pObject)
{
    bool bRet = false;
    const String* pStr = dynamic_cast<const String*>(pObject);
    if (pStr != NULL)
    {
        if (0 == _string.compare(pStr->_string))
        {
            bRet = true;
        }
    }
    return bRet;
}

String* String::create(const std::string& str)
{
    String* pRet = new String(str);
    pRet->autorelease();
    return pRet;
}

String* String::createWithData(const unsigned char* pData, unsigned long nLen)
{
    String* pRet = NULL;
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
            
            pRet = String::create(pStr);
            free(pStr);
        }
    }
    return pRet;
}

String* String::createWithFormat(const char* format, ...)
{
    String* pRet = String::create("");
    va_list ap;
    va_start(ap, format);
    pRet->initWithFormatAndValist(format, ap);
    va_end(ap);

    return pRet;
}

String* String::createWithContentsOfFile(const char* filename)
{
    unsigned long size = 0;
    unsigned char* pData = 0;
    String* pRet = NULL;
    pData = FileUtils::getInstance()->getFileData(filename, "rb", &size);
    pRet = String::createWithData(pData, size);
    CC_SAFE_DELETE_ARRAY(pData);
    return pRet;
}

void String::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

String* String::clone() const
{
    return String::create(_string);
}

NS_CC_END
