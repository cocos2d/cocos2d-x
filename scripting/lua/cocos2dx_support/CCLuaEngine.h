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

#ifndef __CC_LUA_ENGINE_H__
#define __CC_LUA_ENGINE_H__

extern "C" {
#include "lua.h"
}

#include "ccTypes.h"
#include "cocoa/CCObject.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCSet.h"
#include "base_nodes/CCNode.h"
#include "script_support/CCScriptSupport.h"

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


// Lua support for cocos2d-x
class CCLuaEngine : public CCScriptEngineProtocol
{
public:
    static CCLuaEngine* defaultEngine(void);    
    static CCLuaEngine* create(void);
    virtual ~CCLuaEngine(void);
    
    virtual ccScriptType getScriptType() {
        return kScriptTypeLua;
    };

    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByCCObject(CCObject* pObj);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes);
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);

    virtual int executeNodeEvent(CCNode* pNode, int nAction);
    virtual int executeMenuItemEvent(CCMenuItem* pMenuItem);
    virtual int executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName);
    virtual int executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget = NULL);
    virtual int executeSchedule(CCTimer* pTimer, float dt, CCNode* pNode = NULL);
    virtual int executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches);
    virtual int executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch);
    virtual int executeLayerKeypadEvent(CCLayer* pLayer, int eventType);
    /** execute a accelerometer event */
    virtual int executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue);
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) {
        return m_state;
    }

    int pushInt(int data);
    int pushFloat(float data);
    int pushBoolean(bool data);
    int pushString(const char* data);
    int pushString(const char* data, int length);
    int pushNil(void);
    int pushCCObject(CCObject* pObject, const char* typeName);
    int pushCCLuaValue(const CCLuaValue& value);
    int pushCCLuaValueDict(const CCLuaValueDict& dict);
    int pushCCLuaValueArray(const CCLuaValueArray& array);
    int executeFunctionByHandler(int nHandler, int numArgs);
    void cleanStack(void);
    
    // Add lua loader, now it is used on android
    void addLuaLoader(lua_CFunction func);
    
private:
    CCLuaEngine(void)
    : m_state(NULL)
    {
    }
    
    bool init(void);
    bool pushFunction(int nHandler);
    
    lua_State* m_state;
    static CCLuaEngine* m_defaultEngine;
};

NS_CC_END

#endif // __CC_LUA_ENGINE_H__
