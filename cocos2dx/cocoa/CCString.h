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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#include <string.h>
#endif

#include <stdarg.h>
#include <string>
#include <functional>
#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL String : public Object, public Clonable
{
public:
    String();
    String(const char* str);
    String(const std::string& str);
    String(const String& str);

    virtual ~String();
    
    /* override assignment operator */
    String& operator= (const String& other);

    /** init a string with format, it's similar with the c function 'sprintf' */ 
    bool initWithFormat(const char* format, ...) CC_FORMAT_PRINTF(2, 3);

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

    /** compare to a c string */
    int compare(const char *) const;

    /** append additional characters at the end of its current value */
    void append(const std::string& str);

    /** append(w/ format) additional characters at the end of its current value */
    void appendWithFormat(const char* format, ...);

    /** split a string */
    Array* componentsSeparatedByString(const char *delimiter);
    
    /* override functions */
    virtual bool isEqual(const Object* pObject);

    /** create a string with std string, you can also pass a c string pointer because the default constructor of std::string can access a c string pointer. 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static String* create(const std::string& str);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMaxStringLen macro in String.cpp file.
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */ 
    static String* createWithFormat(const char* format, ...) CC_FORMAT_PRINTF(1, 2);

    /** create a string with binary data 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static String* createWithData(const unsigned char* pData, unsigned long nLen);

    /** create a string with a file, 
     *  @return A String pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static String* createWithContentsOfFile(const char* filename);

    virtual void acceptVisitor(DataVisitor &visitor);
    virtual String* clone() const;
    
private:

    /** only for internal use */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string _string;
};

struct StringCompare : public std::binary_function<String *, String *, bool> {
    public:
        bool operator() (String * a, String * b) const {
            return strcmp(a->getCString(), b->getCString()) < 0;
        }
};

#define StringMake(str) String::create(str)
#define ccs               StringMake

// end of data_structure group
/// @}

NS_CC_END

#endif //__CCSTRING_H__
