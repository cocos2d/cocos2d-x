/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "deprecated/CCString.h"
#include "platform/CCFileUtils.h"
#include "base/ccMacros.h"
#include <stdlib.h>
#include <stdio.h>
#include "deprecated/CCArray.h"
#include "base/ccUtils.h"

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
    if (this != &other) {
        _string = other._string;
    }
    return *this;
}

bool __String::initWithFormatAndValist(const char* format, va_list ap)
{
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != nullptr)
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
    _string.clear();

    va_list ap;
    va_start(ap, format);

    bool bRet = initWithFormatAndValist(format, ap);

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
    return (float)utils::atof(_string.c_str());
}

double __String::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return utils::atof(_string.c_str());
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
    if (pBuf != nullptr)
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
    std::string strTmp = _string;
    size_t cutAt;
    while( (cutAt = strTmp.find_first_of(delimiter)) != strTmp.npos )
    {
        if(cutAt > 0)
        {
            result->addObject(__String::create(strTmp.substr(0, cutAt)));
        }
        strTmp = strTmp.substr(cutAt + 1);
    }
    
    if(!strTmp.empty())
    {
        result->addObject(__String::create(strTmp));
    }
    
    return result;
}

bool __String::isEqual(const Ref* pObject)
{
    bool bRet = false;
    const __String* pStr = dynamic_cast<const __String*>(pObject);
    if (pStr != nullptr)
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
    __String* ret = new (std::nothrow) __String(str);
    ret->autorelease();
    return ret;
}

__String* __String::createWithData(const unsigned char* data, size_t nLen)
{
    __String* ret = nullptr;
    if (data != nullptr)
    {
        char* pStr = (char*)malloc(nLen+1);
        if (pStr != nullptr)
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

__String* __String::createWithContentsOfFile(const std::string &filename)
{
    std::string str = FileUtils::getInstance()->getStringFromFile(filename);
    return __String::create(std::move(str));
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
