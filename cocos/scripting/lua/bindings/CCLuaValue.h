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

#include "ccTypes.h"
#include "CCObject.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
using std::memset;
using std::memcpy;
#endif

NS_CC_BEGIN

typedef int LUA_FUNCTION;
typedef int LUA_TABLE;
typedef int LUA_STRING;

class LuaValue;

typedef std::map<std::string, LuaValue>   LuaValueDict;
typedef LuaValueDict::const_iterator      LuaValueDictIterator;
typedef std::list<LuaValue>               LuaValueArray;
typedef LuaValueArray::const_iterator     LuaValueArrayIterator;

typedef enum {
    LuaValueTypeInt,
    LuaValueTypeFloat,
    LuaValueTypeBoolean,
    LuaValueTypeString,
    LuaValueTypeDict,
    LuaValueTypeArray,
    LuaValueTypeObject
} LuaValueType;

typedef union {
    int                 intValue;
    float               floatValue;
    bool                booleanValue;
    std::string*        stringValue;
    LuaValueDict*     dictValue;
    LuaValueArray*    arrayValue;
    Object*           ccobjectValue;
} LuaValueField;

class LuaValue
{
public:
    static const LuaValue intValue(const int intValue);
    static const LuaValue floatValue(const float floatValue);
    static const LuaValue booleanValue(const bool booleanValue);
    static const LuaValue stringValue(const char* stringValue);
    static const LuaValue stringValue(const std::string& stringValue);
    static const LuaValue dictValue(const LuaValueDict& dictValue);
    static const LuaValue arrayValue(const LuaValueArray& arrayValue);
    static const LuaValue ccobjectValue(Object* ccobjectValue, const char* objectTypename);
    static const LuaValue ccobjectValue(Object* ccobjectValue, const std::string& objectTypename);
    
    LuaValue(void)
    : _type(LuaValueTypeInt)
    , _ccobjectType(NULL)
    {
        memset(&_field, 0, sizeof(_field));
    }
    LuaValue(const LuaValue& rhs);
    LuaValue& operator=(const LuaValue& rhs);
    ~LuaValue(void);
    
    const LuaValueType getType(void) const {
        return _type;
    }
    
    const std::string& getObjectTypename(void) const {
        return *_ccobjectType;
    }
    
    int intValue(void) const {
        return _field.intValue;
    }
    
    float floatValue(void) const {
        return _field.floatValue;
    }
    
    bool booleanValue(void) const {
        return _field.booleanValue;
    }
    
    const std::string& stringValue(void) const {
        return *_field.stringValue;
    }
    
    const LuaValueDict& dictValue(void) const {
        return *_field.dictValue;
    }
    
    const LuaValueArray& arrayValue(void) const {
        return *_field.arrayValue;
    }
    
    Object* ccobjectValue(void) const {
        return _field.ccobjectValue;
    }
    
private:
    LuaValueField _field;
    LuaValueType  _type;
    std::string*    _ccobjectType;
    
    void copy(const LuaValue& rhs);
};

NS_CC_END

#endif // __CC_LUA_VALUE_H_
