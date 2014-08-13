/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#include <string.h>
#endif

#include <stdarg.h>
#include <string>
#include <functional>
#include <sstream>
#include "CCArray.h"
#include "base/CCRef.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL __String : public Ref, public Clonable
{
public:
    /**
     * @js NA
     * @lua NA
     */
    __String();
    /**
     * @js NA
     * @lua NA
     */
    __String(const char* str);
    /**
     * @js NA
     * @lua NA
     */
    __String(const std::string& str);
    /**
     * @js NA
     * @lua NA
     */
    __String(const __String& str);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~__String();
    
    /* override assignment operator 
     * @js NA
     * @lua NA
     */
    __String& operator= (const __String& other);

    /** init a string with format, it's similar with the c function 'sprintf' 
     * @js NA
     * @lua NA
     */
    bool initWithFormat(const char* format, ...) CC_FORMAT_PRINTF(2, 3);

    /** convert to int value 
     * @js NA
     */
    int intValue() const;

    /** convert to unsigned int value 
     * @js NA
     */
    unsigned int uintValue() const;

    /** convert to float value 
     * @js NA
     */
    float floatValue() const;

    /** convert to double value 
     * @js NA
     */
    double doubleValue() const;

    /** convert to bool value 
     * @js NA
     */
    bool boolValue() const;

    /** get the C string 
     * @js NA
     */
    const char* getCString() const;

    /** get the length of string 
     * @js NA
     */
    int length() const;

    /** compare to a c string 
     * @js NA
     */
    int compare(const char *) const;

    /** append additional characters at the end of its current value 
     * @js NA
     * @lua NA
     */
    void append(const std::string& str);

    /** append(w/ format) additional characters at the end of its current value 
     * @js NA
     * @lua NA
     */
    void appendWithFormat(const char* format, ...);

    /** split a string 
     * @js NA
     * @lua NA
     */
    __Array* componentsSeparatedByString(const char *delimiter);
    
    /* override functions 
     * @js NA
     */
    virtual bool isEqual(const Ref* pObject);

    /** create a string with std string, you can also pass a c string pointer because the default constructor of std::string can access a c string pointer. 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * @js NA
     */
    static __String* create(const std::string& str);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMax__StringLen macro in __String.cpp file.
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * @js NA
     */
    static __String* createWithFormat(const char* format, ...) CC_FORMAT_PRINTF(1, 2);

    /** create a string with binary data 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * @js NA
     */
    static __String* createWithData(const unsigned char* pData, size_t nLen);

    /** create a string with a file, 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * @js NA
     */
    static __String* createWithContentsOfFile(const std::string& filename);
    /**
     * @js NA
     * @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     * @js NA
     * @lua NA
     */
    virtual __String* clone() const;
    
private:

    /** only for internal use */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string _string;
};

struct StringCompare : public std::binary_function<__String *, __String *, bool> {
    public:
        bool operator() (__String * a, __String * b) const {
            return strcmp(a->getCString(), b->getCString()) < 0;
        }
};

#define StringMake(str) String::create(str)
#define ccs             StringMake

namespace StringUtils {

template<typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

std::string CC_DLL format(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
    
} // namespace StringUtils {

// end of data_structure group
/// @}

NS_CC_END

#endif //__CCSTRING_H__
