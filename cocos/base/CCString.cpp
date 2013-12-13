/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

 http://www.cocos2d-x.org

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

#include "CCString.h"
#include "platform/CCFileUtils.h"
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>
#include "CCArray.h"

NS_CC_BEGIN

#define kMaxStringLen (1024*100)

__String::__String()
    :_string("")
{}

__String::__String(const char * str)
    :_string(str)
{}

__String::__String(const std::string& str)
    :_string(str)
{}

__String::__String(const __String& str)
    :_string(str.getCString())
{}

__String::~__String()
{
    CCLOGINFO("deallocing __String: %p", this);

    _string.clear();
}

__String& __String::operator= (const __String& other)
{
    _string = other._string;
    return *this;
}

bool __String::initWithFormatAndValist(const char* format, va_list ap)
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

bool __String::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    _string.clear();

    va_list ap;
    va_start(ap, format);

    bRet = initWithFormatAndValist(format, ap);

    va_end(ap);

    return bRet;
}

int __String::intValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return atoi(_string.c_str());
}

unsigned int __String::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(_string.c_str());
}

float __String::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(_string.c_str());
}

double __String::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(_string.c_str());
}

bool __String::boolValue() const
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

const char* __String::getCString() const
{
    return _string.c_str();
}

int __String::length() const
{
    return static_cast<int>(_string.length());
}

int __String::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}

void __String::append(const std::string& str)
{
    _string.append(str);
}

void __String::appendWithFormat(const char* format, ...)
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

__Array* __String::componentsSeparatedByString(const char *delimiter)
{
    __Array* result = __Array::create();
    
    size_t cutAt;
    while( (cutAt = _string.find_first_of(delimiter)) != _string.npos )
    {
        if(cutAt > 0)
        {
            result->addObject(__String::create(_string.substr(0, cutAt)));
        }
        _string = _string.substr(cutAt + 1);
    }
    
    if(_string.length() > 0)
    {
        result->addObject(__String::create(_string));
    }
    
    return result;
}

bool __String::isEqual(const Object* pObject)
{
    bool bRet = false;
    const __String* pStr = dynamic_cast<const __String*>(pObject);
    if (pStr != NULL)
    {
        if (0 == _string.compare(pStr->_string))
        {
            bRet = true;
        }
    }
    return bRet;
}

__String* __String::create(const std::string& str)
{
    __String* ret = new __String(str);
    ret->autorelease();
    return ret;
}

__String* __String::createWithData(const unsigned char* data, int nLen)
{
    __String* ret = NULL;
    if (data != NULL)
    {
        char* pStr = (char*)malloc(nLen+1);
        if (pStr != NULL)
        {
            pStr[nLen] = '\0';
            if (nLen > 0)
            {
                memcpy(pStr, data, nLen);
            }
            
            ret = __String::create(pStr);
            free(pStr);
        }
    }
    return ret;
}

__String* __String::createWithFormat(const char* format, ...)
{
    __String* ret = __String::create("");
    va_list ap;
    va_start(ap, format);
    ret->initWithFormatAndValist(format, ap);
    va_end(ap);

    return ret;
}

__String* __String::createWithContentsOfFile(const char* filename)
{
    ssize_t size = 0;
    unsigned char* data = 0;
    __String* ret = NULL;
    data = FileUtils::getInstance()->getFileData(filename, "rb", &size);
    ret = __String::createWithData(data, static_cast<int>(size));
    free(data);
    return ret;
}

void __String::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

__String* __String::clone() const
{
    return __String::create(_string);
}

NS_CC_END
