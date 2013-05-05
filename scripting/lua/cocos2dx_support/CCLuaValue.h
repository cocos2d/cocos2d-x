/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org
 
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
#include "cocoa/CCObject.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
using std::memset;
using std::memcpy;
#endif

NS_CC_BEGIN

typedef int LUA_FUNCTION;
typedef int LUA_TABLE;
typedef int LUA_STRING;

class CCLuaValue;

typedef std::map<std::string, CCLuaValue>   CCLuaValueDict;
typedef CCLuaValueDict::const_iterator      CCLuaValueDictIterator;
typedef std::list<CCLuaValue>               CCLuaValueArray;
typedef CCLuaValueArray::const_iterator     CCLuaValueArrayIterator;

typedef enum {
    CCLuaValueTypeInt,
    CCLuaValueTypeFloat,
    CCLuaValueTypeBoolean,
    CCLuaValueTypeString,
    CCLuaValueTypeDict,
    CCLuaValueTypeArray,
    CCLuaValueTypeCCObject
} CCLuaValueType;

typedef union {
    int                 intValue;
    float               floatValue;
    bool                booleanValue;
    std::string*        stringValue;
    CCLuaValueDict*     dictValue;
    CCLuaValueArray*    arrayValue;
    CCObject*           ccobjectValue;
} CCLuaValueField;

class CCLuaValue
{
public:
    static const CCLuaValue intValue(const int intValue);
    static const CCLuaValue floatValue(const float floatValue);
    static const CCLuaValue booleanValue(const bool booleanValue);
    static const CCLuaValue stringValue(const char* stringValue);
    static const CCLuaValue stringValue(const std::string& stringValue);
    static const CCLuaValue dictValue(const CCLuaValueDict& dictValue);
    static const CCLuaValue arrayValue(const CCLuaValueArray& arrayValue);
    static const CCLuaValue ccobjectValue(CCObject* ccobjectValue, const char* objectTypename);
    static const CCLuaValue ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename);
    
    CCLuaValue(void)
    : m_type(CCLuaValueTypeInt)
    , m_ccobjectType(NULL)
    {
        memset(&m_field, 0, sizeof(m_field));
    }
    CCLuaValue(const CCLuaValue& rhs);
    CCLuaValue& operator=(const CCLuaValue& rhs);
    ~CCLuaValue(void);
    
    const CCLuaValueType getType(void) const {
        return m_type;
    }
    
    const std::string& getCCObjectTypename(void) const {
        return *m_ccobjectType;
    }
    
    int intValue(void) const {
        return m_field.intValue;
    }
    
    float floatValue(void) const {
        return m_field.floatValue;
    }
    
    bool booleanValue(void) const {
        return m_field.booleanValue;
    }
    
    const std::string& stringValue(void) const {
        return *m_field.stringValue;
    }
    
    const CCLuaValueDict& dictValue(void) const {
        return *m_field.dictValue;
    }
    
    const CCLuaValueArray& arrayValue(void) const {
        return *m_field.arrayValue;
    }
    
    CCObject* ccobjectValue(void) const {
        return m_field.ccobjectValue;
    }
    
private:
    CCLuaValueField m_field;
    CCLuaValueType  m_type;
    std::string*    m_ccobjectType;
    
    void copy(const CCLuaValue& rhs);
};

NS_CC_END

#endif // __CC_LUA_VALUE_H_
