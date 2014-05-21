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
    
    /* 重载赋值运算符
     * @js NA
     * @lua NA
     */
    __String& operator= (const __String& other);

    /** 初始化字符串格式, 和C语言的'sprintf' 函数类似
     * @js NA
     * @lua NA
     */
    bool initWithFormat(const char* format, ...) CC_FORMAT_PRINTF(2, 3);

    /** 转换为int类型 的值
     * @js NA
     */
    int intValue() const;

    /** 转化为unsigned int 的值 
     * @js NA
     */
    unsigned int uintValue() const;

    /** 转化为float value 
     * @js NA
     */
    float floatValue() const;

    /** 转化为 double value 
     * @js NA
     */
    double doubleValue() const;

    /** 转化为 bool value 
     * @js NA
     */
    bool boolValue() const;

    /** 获取C string 
     * @js NA
     */
    const char* getCString() const;

    /** 获取 string长度 
     * @js NA
     */
    int length() const;

    /** 比较C String 
     * @js NA
     */
    int compare(const char *) const;

    /** 在当前字符串的末尾追加额外的字符
     * @js NA
     * @lua NA
     */
    void append(const std::string& str);

    /** 追加(w/ 格式) 额外的字符 在当前字符串末尾 
     * @js NA
     * @lua NA
     */
    void appendWithFormat(const char* format, ...);

    /** 分开一个string 
     * @js NA
     * @lua NA
     */
    __Array* componentsSeparatedByString(const char *delimiter);
    
    /* 重载方法
     * @js NA
     */
    virtual bool isEqual(const Ref* pObject);

    /** 根据std string创建一个string, 你也能使用一个 c string 指针 因为默认的 std::string构造 能得到一个 c string 指针. 
     *  @return 一个String pointer是一个 autorelease 对象的 pointer,
     *          i这意味着你不需要release 操作 除非 你 retain 了它.
     * @js NA
     */
    static __String* create(const std::string& str);

    /** 根据某个格式创建一个string, 它和 c语言 函数 'sprintf'类似, 默认的 buffer 大小是 (1024*100) bytes,
     *  如果你想改变这个值, 你需要在__String.cpp 文件里面改变 kMax__StringLen 这个宏 .
     *  @return 这是一个 autorelease object pointer,
     *          所以你不需要release 操作除非你 retain 了它.
     * @js NA
     */
    static __String* createWithFormat(const char* format, ...) CC_FORMAT_PRINTF(1, 2);

    /** 创建一个二进制数据的字符串 
     *  @return 这是一个 autorelease object pointer,
     *          所以你不需要release 操作除非你 retain 了它.
     * @js NA
     */
    static __String* createWithData(const unsigned char* pData, size_t nLen);

    /** 创建一个文件名字字符串, 
     *  @return 这是一个 autorelease object pointer,
     *          所以你不需要release 操作除非你 retain 了它.
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

std::string format(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
    
} // namespace StringUtils {

// end of data_structure group
/// @}

NS_CC_END

#endif //__CCSTRING_H__
