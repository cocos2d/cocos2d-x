/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __CCSTRING_H__
#define __CCSTRING_H__

#include <string>
#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL CCString : public CCObject
{
public:
    CCString();
    CCString(const char* str);
    CCString(const std::string& str);
    CCString(const CCString& str);

    virtual ~CCString();
    
    /* override assignment operator */
    CCString& operator= (const CCString& other);

    /** init a string with format, it's similar with the c function 'sprintf' */ 
    bool initWithFormat(const char* format, ...);

    /** convert to int value */
    int intValue() const;

    /** convert to unsigned int value */
    unsigned int uintValue() const;

    /** convert to float value */
    float floatValue() const;

    /** convert to double value */
    double doubleValue() const;

    /** convert to bool value */
    bool boolValue() const;

    /** get the C string */
    const char* getCString() const;

    /** get the length of string */
    unsigned int length() const;

    /* override functions */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual bool isEqual(const CCObject* pObject);

    /* static funcitons */
    /** create a string with c string 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static CCString* stringWithCString(const char* pStr);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMaxStringLen macro in CCString.cpp file.
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */ 
    static CCString* stringWithFormat(const char* format, ...);

    /** create a string with binary data 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static CCString* stringWithData(unsigned char* pData, unsigned long nLen);

    /** create a string with a file, 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static CCString* stringWithContentsOfFile(const char* pszFileName);

private:

    /** only for internal use */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string m_sString;
};

#define CCStringMake(str) CCString::stringWithCString(str)
#define ccs               CCStringMake


NS_CC_END

#endif //__CCSTRING_H__