/****************************************************************************
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

#ifndef __cocos2d_libs__CCValue__
#define __cocos2d_libs__CCValue__

#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include <string>
#include <vector>
#include <unordered_map>

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Value;

typedef std::vector<Value> ValueVector;
typedef std::unordered_map<std::string, Value> ValueMap;
typedef std::unordered_map<int, Value> ValueMapIntKey;

CC_DLL extern const ValueVector ValueVectorNull;
CC_DLL extern const ValueMap ValueMapNull;
CC_DLL extern const ValueMapIntKey ValueMapIntKeyNull;

/*
 * @~english This class is provide as a wrapper of basic types, such as int and bool.
 * @~chinese 这个类提供基本类型的wrapper,如int和bool。
 */
class CC_DLL Value
{
public:

    /** @~english A predefined Value that has not value.  @~chinese 一个预定义的空值。*/
    static const Value Null;

    /** @~english Default constructor.  @~chinese 默认构造函数。*/
    Value();
    
    /** @~english Create a Value by an unsigned char value.  @~chinese 由一个无符号字符值创建一个Value。*/
    explicit Value(unsigned char v);
    
    /** @~english Create a Value by an integer value.  @~chinese 由一个整数创建一个Value。*/
    explicit Value(int v);
    
    /** @~english Create a Value by a float value.  @~chinese 由一个浮点数创建一个Value。*/
    explicit Value(float v);
    
    /** @~english Create a Value by a double value.  @~chinese 从一个双精度数字创建一个Value。*/
    explicit Value(double v);
    
    /** @~english Create a Value by a bool value.  @~chinese 从一个bool值创建一个Value。*/
    explicit Value(bool v);
    
    /** @~english Create a Value by a char pointer. It will copy the chars internally.  @~chinese 从一个字符指针创建一个Value。它将复制字符内部。*/
    explicit Value(const char* v);
    
    /** @~english Create a Value by a string.  @~chinese 从一个字符串创建一个Value。*/
    explicit Value(const std::string& v);
    
    /** @~english Create a Value by a ValueVector object.  @~chinese 使用ValueVector对象创建一个Value。*/
    explicit Value(const ValueVector& v);

    /** @~english Create a Value by a ValueVector object. It will use std::move internally.  @~chinese 使用ValueVector对象创建一个Value。它将使用std::move移动到内部。*/
    explicit Value(ValueVector&& v);
    
    /** @~english Create a Value by a ValueMap object.  @~chinese 使用ValueMap对象创建一个Value。*/
    explicit Value(const ValueMap& v);

    /** @~english Create a Value by a ValueMap object. It will use std::move internally.  @~chinese 使用ValueMap对象创建一个Value。它将使用std::move移动到内部。*/
    explicit Value(ValueMap&& v);
    
    /** @~english Create a Value by a ValueMapIntKey object.  @~chinese 使用ValueMapIntKey创建一个Value对象。*/
    explicit Value(const ValueMapIntKey& v);

    /** @~english Create a Value by a ValueMapIntKey object. It will use std::move internally.  @~chinese 使用ValueMapIntKey创建一个Value对象。它将使用std::move移动到内部。*/
    explicit Value(ValueMapIntKey&& v);

    /** @~english Create a Value by another Value object.  @~chinese 使用一个Value创建另一个Value。*/
    Value(const Value& other);

    /** @~english Create a Value by a Value object. It will use std::move internally.  @~chinese 使用一个Value创建另一个Value。它将使用std::move移动到内部。*/
    Value(Value&& other);
    
    /** @~english Destructor.  @~chinese 析构函数。*/
    ~Value();

    /** @~english Assignment operator, assign from Value to Value.  @~chinese 赋值运算符,从Value赋值到Value。*/
    Value& operator= (const Value& other);

    /** @~english Assignment operator, assign from Value to Value. It will use std::move internally.  @~chinese 赋值运算符,从Value赋值到Value。它将使用std::move移动到内部。*/
    Value& operator= (Value&& other);

    /** @~english Assignment operator, assign from unsigned char to Value.  @~chinese 赋值运算符，从无符号字符赋值。*/
    Value& operator= (unsigned char v);

    /** @~english Assignment operator, assign from integer to Value.  @~chinese 赋值运算符,从整数赋值。*/
    Value& operator= (int v);

    /** @~english Assignment operator, assign from float to Value.  @~chinese 赋值运算符,从浮点数赋值。*/
    Value& operator= (float v);

    /** @~english Assignment operator, assign from double to Value.  @~chinese 赋值运算符,从双精度数字赋值。*/
    Value& operator= (double v);

    /** @~english Assignment operator, assign from bool to Value.  @~chinese 赋值运算符,从布尔值赋值。*/
    Value& operator= (bool v);

    /** @~english Assignment operator, assign from string to Value.  @~chinese 赋值运算符,从字符串赋值。*/
    Value& operator= (const std::string& v);

    /** @~english Assignment operator, assign from ValueVector to Value.  @~chinese 赋值运算符,从ValueVector赋值。*/
    Value& operator= (const ValueVector& v);

    /** @~english Assignment operator, assign from ValueVector to Value.  @~chinese 赋值运算符,从ValueVector赋值。*/
    Value& operator= (ValueVector&& v);

    /** @~english Assignment operator, assign from ValueMap to Value.  @~chinese 赋值运算符,从ValueMap赋值。*/
    Value& operator= (const ValueMap& v);

    /** @~english Assignment operator, assign from ValueMap to Value. It will use std::move internally.  @~chinese 赋值运算符,从ValueMap分配值。它将使用std::move移动到内部。*/
    Value& operator= (ValueMap&& v);

    /** @~english Assignment operator, assign from ValueMapIntKey to Value.  @~chinese赋值运算符,从ValueMapIntKey赋值。*/
    Value& operator= (const ValueMapIntKey& v);

    /** @~english Assignment operator, assign from ValueMapIntKey to Value. It will use std::move internally.  @~chinese赋值运算符,从ValueMapIntKey赋值。它将使用std::move移动到内部。*/
    Value& operator= (ValueMapIntKey&& v);

    /** @~english != operator overloading  @~chinese != 操作符重载*/
    bool operator!= (const Value& v);

    /** @~english != operator overloading  @~chinese != 操作符重载*/
    bool operator!= (const Value& v) const;

    /** @~english == operator overloading  @~chinese == 操作符重载*/
    bool operator== (const Value& v);

    /** @~english == operator overloading  @~chinese == 操作符重载*/
    bool operator== (const Value& v) const;

    /** @~english Gets as a byte value. Will convert to unsigned char if possible, or will trigger assert error.  @~chinese 获取一个字节值。如果可能将转换为无符号字符,否则引发断言错误。*/
    unsigned char asByte() const;

    /** @~english Gets as an integer value. Will convert to integer if possible, or will trigger assert error.  @~chinese 获取一个整数值。如果可能将转换为整数,否则引发断言错误。*/
    int asInt() const;

    /** @~english Gets as a float value. Will convert to float if possible, or will trigger assert error.  @~chinese 获取一个浮点数。如果可能将转换为浮动,否则引发断言错误。*/
    float asFloat() const;

    /** @~english Gets as a double value. Will convert to double if possible, or will trigger assert error.  @~chinese 获取一个双精度数。如果可能将转换为双,否则引发断言错误。*/
    double asDouble() const;

    /** @~english Gets as a bool value. Will convert to bool if possible, or will trigger assert error.  @~chinese 获取一个bool值。如果可能将转换为bool,否则引发断言错误。*/
    bool asBool() const;

    /** @~english Gets as a string value. Will convert to string if possible, or will trigger assert error.  @~chinese 获取一个字符串。如果可能将转换为字符串,否则引发断言错误。*/
    std::string asString() const;

    /** @~english Gets as a ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error.  @~chinese 获取ValueVector。如果可能将转换为ValueVector,否则引发断言错误。*/
    ValueVector& asValueVector();

    /** @~english Gets as a const ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error.  @~chinese 获取一个常量ValueVector。如果可能将转换为ValueVector,否则引发断言错误。*/
    const ValueVector& asValueVector() const;

    /** @~english Gets as a ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error.  @~chinese 获取ValueMap。如果可能将转换为ValueMap,否则引发断言错误。*/
    ValueMap& asValueMap();

    /** @~english Gets as a const ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error.  @~chinese 获取一个一个常量ValueMap。如果可能将转换为ValueMap,否则引发断言错误。*/
    const ValueMap& asValueMap() const;

    /** @~english Gets as a ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error.  @~chinese 获取ValueMapIntKey。如果可能将转换为ValueMapIntKey,否则引发断言错误。*/
    ValueMapIntKey& asIntKeyMap();

    /** @~english Gets as a const ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error.  @~chinese 获取一个常量ValueMapIntKey。如果可能将转换为ValueMapIntKey,否则引发断言错误。*/
    const ValueMapIntKey& asIntKeyMap() const;

    /**
     * @~english Checks if the Value is null.
     * @~chinese  检查值是否为null。
     * @return @~english True if the Value is null, false if not.
     * @~chinese 如果该值为null则为true,否则为false。
     */
    inline bool isNull() const { return _type == Type::NONE; }

    /** @~english Value type wrapped by Value.  @~chinese Value的类型。*/
    enum class Type
    {
        /// no value is wrapped, an empty Value
        NONE = 0,
        /// wrap byte
        BYTE,
        /// wrap integer
        INTEGER,
        /// wrap float
        FLOAT,
        /// wrap double
        DOUBLE,
        /// wrap bool
        BOOLEAN,
        /// wrap string
        STRING,
        /// wrap vector
        VECTOR,
        /// wrap ValueMap
        MAP,
        /// wrap ValueMapIntKey
        INT_KEY_MAP
    };

    /** @~english Gets the value type.  @~chinese 获取Value的类型。*/
    inline Type getType() const { return _type; }

    /** @~english Gets the description of the class.  @~chinese 获取Value类的描述。*/
    std::string getDescription() const;

private:
    void clear();
    void reset(Type type);

    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;

        std::string* strVal;
        ValueVector* vectorVal;
        ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
    }_field;

    Type _type;
};

/** @} */

NS_CC_END


#endif /* defined(__cocos2d_libs__CCValue__) */
