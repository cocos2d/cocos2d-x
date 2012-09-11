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

// #pragma mark -
// #pragma mark CCScriptValue

class CCScriptValue;

typedef std::map<std::string, CCScriptValue>    CCScriptValueDict;
typedef CCScriptValueDict::const_iterator       CCScriptValueDictIterator;
typedef std::list<CCScriptValue>                CCScriptValueArray;
typedef CCScriptValueArray::const_iterator      CCScriptValueArrayIterator;

typedef enum {
    CCScriptValueTypeInt,
    CCScriptValueTypeFloat,
    CCScriptValueTypeBoolean,
    CCScriptValueTypeString,
    CCScriptValueTypeDict,
    CCScriptValueTypeArray,
    CCScriptValueTypeCCObject
} CCScriptValueType;

typedef union {
    int                 intValue;
    float               floatValue;
    bool                booleanValue;
    std::string*        stringValue;
    CCScriptValueDict*  dictValue;
    CCScriptValueArray* arrayValue;
    CCObject*           ccobjectValue;
} CCScriptValueField;

class CCScriptValue
{
public:
    static const CCScriptValue intValue(const int intValue);
    static const CCScriptValue floatValue(const float floatValue);
    static const CCScriptValue booleanValue(const bool booleanValue);
    static const CCScriptValue stringValue(const char* stringValue);
    static const CCScriptValue stringValue(const std::string& stringValue);
    static const CCScriptValue dictValue(const CCScriptValueDict& dictValue);
    static const CCScriptValue arrayValue(const CCScriptValueArray& arrayValue);
    static const CCScriptValue ccobjectValue(CCObject* ccobjectValue, const char* objectTypename);
    static const CCScriptValue ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename);

    CCScriptValue(void)
        : m_type(CCScriptValueTypeInt)
        , m_ccobjectType(NULL)
    {
        memset(&m_field, 0, sizeof(m_field));
    }
    CCScriptValue(const CCScriptValue& rhs);
    CCScriptValue& operator=(const CCScriptValue& rhs);
    ~CCScriptValue(void);

    const CCScriptValueType getType(void) const {
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

    const CCScriptValueDict& dictValue(void) const {
        return *m_field.dictValue;
    }

    const CCScriptValueArray& arrayValue(void) const {
        return *m_field.arrayValue;
    }

    CCObject* ccobjectValue(void) const {
        return m_field.ccobjectValue;
    }

private:
    CCScriptValueField  m_field;
    CCScriptValueType   m_type;
    std::string*        m_ccobjectType;

    void copy(const CCScriptValue& rhs);
};


// Lua support for cocos2d-x
class CCLuaEngine : public CCScriptEngineProtocol
{
public:
    static CCLuaEngine* create(void);
    ~CCLuaEngine(void);
    
    virtual ccScriptType getScriptType() { return kScriptTypeLua; };
    
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    virtual lua_State* getLuaState(void) {
        return m_state;
    }

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

    virtual int pushIntegerData(int data);
    virtual int pushFloatData(float data);
    virtual int pushBooleanData(bool data);
    virtual int pushStringData(const char* data);
    virtual int pushCCObject(CCObject* pObject, const char* typeName);
    virtual int pushCCScriptValue(const CCScriptValue& value);
    virtual int pushCCScriptValueDict(const CCScriptValueDict& dict);
    virtual int pushCCScriptValueArray(const CCScriptValueArray& array);
    int executeFunctionByHandler(int nHandler, int numArgs);
    virtual void cleanStack(void);
    
    // Add lua loader, now it is used on android
    virtual void addLuaLoader(lua_CFunction func);
    
private:
    CCLuaEngine(void)
    : m_state(NULL)
    {
    }
    
    bool init(void);
    bool pushFunction(int nHandler);
    
    lua_State* m_state;
};

NS_CC_END

#endif // __CC_LUA_ENGINE_H__
