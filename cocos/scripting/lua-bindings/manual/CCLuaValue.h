/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CC_LUA_VALUE_H_
#define __CC_LUA_VALUE_H_

#include <string>
#include <map>
#include <list>

extern "C" {
#include "lua.h"
}

#include "base/ccTypes.h"
#include "base/CCRef.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
using std::memset;
using std::memcpy;
#endif

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

typedef int LUA_FUNCTION;
typedef int LUA_TABLE;
typedef int LUA_STRING;

class LuaValue;

typedef std::map<std::string, LuaValue>   LuaValueDict;
typedef LuaValueDict::const_iterator      LuaValueDictIterator;
typedef std::list<LuaValue>               LuaValueArray;
typedef LuaValueArray::const_iterator     LuaValueArrayIterator;

/// @cond
typedef enum {
    LuaValueTypeInt,
    LuaValueTypeFloat,
    LuaValueTypeBoolean,
    LuaValueTypeString,
    LuaValueTypeDict,
    LuaValueTypeArray,
    LuaValueTypeObject
} LuaValueType;
/// @endcond

/// @cond
typedef union {
    int                 intValue;
    float               floatValue;
    bool                booleanValue;
    std::string*        stringValue;
    LuaValueDict*     dictValue;
    LuaValueArray*    arrayValue;
    Ref*           ccobjectValue;
} LuaValueField;
/// @endcond

/**@~english
 * Wrap different general types of data into a same specific type named LuaValue.
 * The general types supported are as follows:int,float,bool,std::string,const char*,LuaValueDict,LuaValueArray,Ref object.
 *
 * @~chinese 
 * LuaValue是一些常规类型数据的高级封装。
 * 支持的常规类型如下:int,float,bool,std::string,const char*,LuaValueDict,LuaValueArray,Ref object.
 * 
 * @lua NA
 * @js NA
 */
class LuaValue
{
public:
    
    /**@~english
     * Construct a LuaValue object by a int value.
     *
     * @~chinese 
     * 通过一个int值构建一个LuaValue对象。
     * 
     * @param intValue @~english a int value.
     * @~chinese int值。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue intValue(const int intValue);
    
    /**@~english
     * Construct a LuaValue object by a float value.
     *
     * @~chinese 
     * 通过一个float值构建一个LuaValue对象。
     * 
     * @param floatValue @~english a float value.
     * @~chinese float值。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue floatValue(const float floatValue);
    
    /**@~english
     * Construct a LuaValue object by a boolean value.
     *
     * @~chinese 
     * 通过一个bool值构建一个LuaValue对象。
     * 
     * @param booleanValue @~english a bool value.
     * @~chinese bool值。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue booleanValue(const bool booleanValue);
    
    /**@~english
     * Construct a LuaValue object by a string pointer.
     *
     * @~chinese 
     * 通过一个字符串指针构建一个LuaValue对象。
     * 
     * @param stringValue @~english a string pointer.
     * @~chinese 字符串指针。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue stringValue(const char* stringValue);
    
    /**@~english
     * Construct a LuaValue object by a std::string object.
     *
     * @~chinese 
     * 通过一个std::string字符串构建一个LuaValue对象。
     * 
     * @param stringValue @~english a std::string object.
     * @~chinese std::string字符串。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue stringValue(const std::string& stringValue);
    
    /**@~english
     * Construct a LuaValue object by a LuaValueDict value.
     *
     * @~chinese 
     * 通过一个LuaValueDict对象构造一个LuaValue对象。
     * 
     * @param dictValue @~english a LuaValueDict object.
     * @~chinese LuaValueDict对象。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue dictValue(const LuaValueDict& dictValue);
    
    /**@~english
     * Construct a LuaValue object by a LuaValueArray value.
     *
     * @~chinese 
     * 通过一个LuaValueArray对象构造一个LuaValue对象。
     * 
     * @param arrayValue @~english a LuaValueArray object.
     * @~chinese LuaValueArray对象。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue arrayValue(const LuaValueArray& arrayValue);
    
    /**@~english
     * Construct a LuaValue object by a Ref object and the type name of object.
     *
     * @~chinese 
     * 通过一个Ref对象以及对应的类型名字构造一个LuaValue对象。
     * 
     * @param ccobjectValue @~english a Ref object.
     * @~chinese Ref对象。
     * @param objectTypename @~english a string pointer point to the typename of object.
     * @~chinese 一个指向对象类型名字的字符串指针。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue ccobjectValue(Ref* ccobjectValue, const char* objectTypename);
    
    /**@~english
     * Construct a LuaValue object by a Ref object.
     *
     * @~chinese 
     * 通过一个Ref对象以及对应的类型名字构造一个LuaValue对象
     * 
     * @param ccobjectValue @~english a Ref object.
     * @~chinese Ref对象。
     * @param objectTypename @~english a std::string object represent the typename of object.
     * @~chinese 一个用std::string表示的对象类型名字。
     * @return @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */
    static const LuaValue ccobjectValue(Ref* ccobjectValue, const std::string& objectTypename);
    
    
    /**@~english
     * Default constuctor of LuaValue.
     * Set the default value for _type and _ccobjectType,and init the _field.
     * @~chinese 
     * LuaValue的默认构造函数。
     * 设置_type，_ccobjectType的默认值,同时初始化_field。
     */
    LuaValue(void)
    : _type(LuaValueTypeInt)
    , _ccobjectType(nullptr)
    {
        memset(&_field, 0, sizeof(_field));
    }
    
    /**@~english
     * Copy constructor of LuaValue.
     * @~chinese 
     * 拷贝构造函数。
     */
    LuaValue(const LuaValue& rhs);
    
    /**@~english
     * Override of operator= .
     * @~chinese 
     * 赋值操作符重载函数。
     */
    LuaValue& operator=(const LuaValue& rhs);
    
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~LuaValue(void);
    
    /**@~english
     * Get the type of LuaValue object.
     * 
     * @~chinese 
     * LuaValue对象的类型。
     * 
     * @return @~english the type of LuaValue object.
     * @~chinese LuaValue对象的类型。
     */
    const LuaValueType getType(void) const {
        return _type;
    }
    
    /**@~english
     * Get the typename of the Ref object.
     *
     * @~chinese 
     * 得到Ref对象的类型名字。
     * 
     * @return @~english the type name of Ref object.
     * @~chinese Ref对象的类型名字。
     */
    const std::string& getObjectTypename(void) const {
        return *_ccobjectType;
    }
    
    /**@~english
     * Get the int value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的int值。
     * 
     * @return @~english the int value.
     * @~chinese int值。
     */
    int intValue(void) const {
        return _field.intValue;
    }
    
    /**@~english
     * Get the float value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的float值。
     * 
     * @return @~english the float value.
     * @~chinese float值。
     */
    float floatValue(void) const {
        return _field.floatValue;
    }
    
    /**@~english
     * Get the boolean value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的bool值。
     * 
     * @return @~english the boolean value.
     * @~chinese bool值。
     */
    bool booleanValue(void) const {
        return _field.booleanValue;
    }
    
    /**@~english
     * Get the std::string value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的std::string值。
     * 
     * @return @~english the refrence about string value.
     * @~chinese std::string值。
     */
    const std::string& stringValue(void) const {
        return *_field.stringValue;
    }
    
    /**@~english
     * Get the LuaValueDict value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的LuaValueDict值。
     * 
     * @return @~english the LuaValueDict value.
     * @~chinese LuaValueDict值。
     */
    const LuaValueDict& dictValue(void) const {
        return *_field.dictValue;
    }
    
    /**@~english
     * Get the LuaValueArray value of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的LuaValueArray值。
     * 
     * @return @~english the LuaValueArray value.
     * @~chinese LuaValueArray值。
     */
    const LuaValueArray& arrayValue(void) const {
        return *_field.arrayValue;
    }
    
    /**@~english
     * Get the Ref object of LuaValue object.
     *
     * @~chinese 
     * 获取LuaValue对象的Ref对象指针。
     * 
     * @return @~english the pointer point to a Ref object.
     * @~chinese Ref对象指针。
     */
    Ref* ccobjectValue(void) const {
        return _field.ccobjectValue;
    }
    
private:
    LuaValueField _field;
    LuaValueType  _type;
    std::string*    _ccobjectType;
    
    void copy(const LuaValue& rhs);
};

NS_CC_END

// end group
/// @}
#endif // __CC_LUA_VALUE_H_
