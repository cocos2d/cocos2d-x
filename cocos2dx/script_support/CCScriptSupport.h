/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "platform/CCCommon.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCSet.h"
#include <map>
#include <string>
#include <list>

typedef struct lua_State lua_State;

NS_CC_BEGIN

typedef int LUA_FUNCTION;
typedef int LUA_TABLE;
typedef int LUA_STRING;

#pragma mark -
#pragma mark CCScriptHandlerEntry

class CCScriptHandlerEntry : public CCObject
{
public:
    static CCScriptHandlerEntry* create(int nHandler);
    ~CCScriptHandlerEntry(void);
    
    int getHandler(void) {
        return m_nHandler;
    }
    
    int getEntryId(void) {
        return m_nEntryId;
    }
    
protected:
    CCScriptHandlerEntry(int nHandler)
    : m_nHandler(nHandler)
    {
        static int newEntryId = 0;
        newEntryId++;
        m_nEntryId = newEntryId;
    }
    
    int m_nHandler;
    int m_nEntryId;
};


#pragma mark -
#pragma mark CCSchedulerScriptHandlerEntry

class CCTimer;

class CCSchedulerScriptHandlerEntry : public CCScriptHandlerEntry
{
public:
    // nHandler return by tolua_ref_function(), called from LuaCocos2d.cpp
    static CCSchedulerScriptHandlerEntry* create(int nHandler, float fInterval, bool bPaused);
    ~CCSchedulerScriptHandlerEntry(void);
    
    cocos2d::CCTimer* getTimer(void) {
        return m_pTimer;
    }
    
    bool isPaused(void) {
        return m_bPaused;
    }
    
    void markedForDeletion(void) {
        m_bMarkedForDeletion = true;
    }
    
    bool isMarkedForDeletion(void) {
        return m_bMarkedForDeletion;
    }
    
private:
    CCSchedulerScriptHandlerEntry(int nHandler)
    : CCScriptHandlerEntry(nHandler)
    , m_pTimer(NULL)
    , m_bPaused(false)
    , m_bMarkedForDeletion(false)
    {
    }
    bool init(float fInterval, bool bPaused);
    
    cocos2d::CCTimer*   m_pTimer;
    bool                m_bPaused;
    bool                m_bMarkedForDeletion;
};


#pragma mark -
#pragma mark CCTouchScriptHandlerEntry

class CCTouchScriptHandlerEntry : public CCScriptHandlerEntry
{
public:
    static CCTouchScriptHandlerEntry* create(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    ~CCTouchScriptHandlerEntry(void);
    
    bool isMultiTouches(void) {
        return m_bIsMultiTouches;
    }
    
    int getPriority(void) {
        return m_nPriority;
    }
    
    bool getSwallowsTouches(void) {
        return m_bSwallowsTouches;
    }
    
private:
    CCTouchScriptHandlerEntry(int nHandler)
    : CCScriptHandlerEntry(nHandler)
    , m_bIsMultiTouches(false)
    , m_nPriority(0)
    , m_bSwallowsTouches(false)
    {
    }
    bool init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    
    bool    m_bIsMultiTouches;
    int     m_nPriority;
    bool    m_bSwallowsTouches;
};

#pragma mark -
#pragma mark LuaValue

class LuaValue;

typedef std::map<std::string, LuaValue> LuaDict;
typedef LuaDict::const_iterator         LuaDictIterator;
typedef std::list<LuaValue>             LuaArray;
typedef LuaArray::const_iterator        LuaArrayIterator;

typedef enum {
    LuaValueTypeInt,
    LuaValueTypeFloat,
    LuaValueTypeBoolean,
    LuaValueTypeString,
    LuaValueTypeDict,
    LuaValueTypeArray,
    LuaValueTypeCCObject
} LuaValueType;

typedef union {
    int             intValue;
    float           floatValue;
    bool            booleanValue;
    std::string*    stringValue;
    LuaDict*        dictValue;
    LuaArray*       arrayValue;
    CCObject*       ccobjectValue;
} LuaValueField;

class CC_DLL LuaValue
{
public:
    static const LuaValue intValue(const int intValue);
    static const LuaValue floatValue(const float floatValue);
    static const LuaValue booleanValue(const bool booleanValue);
    static const LuaValue stringValue(const char* stringValue);
    static const LuaValue stringValue(const std::string& stringValue);
    static const LuaValue dictValue(const LuaDict& dictValue);
    static const LuaValue arrayValue(const LuaArray& arrayValue);
    static const LuaValue ccobjectValue(CCObject* ccobjectValue, const char* objectTypename);
    static const LuaValue ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename);
    
    LuaValue(void)
    : m_type(LuaValueTypeInt)
    , m_ccobjectType(NULL)
    {
        memset(&m_field, 0, sizeof(m_field));
    }
    LuaValue(const LuaValue& rhs);
    LuaValue& operator=(const LuaValue& rhs);
    ~LuaValue(void);
    
    const LuaValueType getType(void) const {
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
    
    const LuaDict& dictValue(void) const {
        return *m_field.dictValue;
    }
    
    const LuaArray& arrayValue(void) const {
        return *m_field.arrayValue;
    }
    
    CCObject* ccobjectValue(void) const {
        return m_field.ccobjectValue;
    }
    
private:
    LuaValueField   m_field;
    LuaValueType    m_type;
    std::string*    m_ccobjectType;
    
    void copy(const LuaValue& rhs);
};


#pragma mark -
#pragma mark CCScriptEngineProtocol

class CC_DLL CCScriptEngineProtocol : public CCObject
{
public:
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    virtual lua_State* getLuaState(void) = 0;
    
    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    virtual void removeCCObjectByID(int nLuaID) = 0;
    
    /**
     @brief Remove Lua function handler
     */
    virtual void removeLuaHandler(int nHandler) = 0;
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path) = 0;
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes) = 0;
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    /**
     @brief Execute a function by handler
     @param The function handler
     @param Number of parameters
     @return The integer value returned from the script function.
     */
    virtual int executeFunction(int nHandler, int numArgs) = 0;
    virtual int executeFunctionWithInt(int nHandler, int data) = 0;
    virtual int executeFunctionWithFloat(int nHandler, float data) = 0;
    virtual int executeFunctionWithBool(int nHandler, bool data) = 0;
    virtual int executeFunctionWithCCObject(int nHandler, CCObject* pObject, const char* typeName) = 0;    
    virtual int pushInt(int data) = 0;
    virtual int pushFloat(float data) = 0;
    virtual int pushBool(bool data) = 0;
    virtual int pushString(const char* data) = 0;
    virtual int pushCCObject(CCObject* pObject, const char* typeName) = 0;
    virtual int pushLuaValue(const LuaValue& value) = 0;
    virtual int pushLuaDict(const LuaDict& dict) = 0;
    virtual int pushLuaArray(const LuaArray& array) = 0;
    virtual void cleanStack(void) = 0;
    
    // functions for excute touch event
    virtual int executeTouchEvent(int nHandler, int eventType, CCTouch *pTouch) = 0;
    virtual int executeTouchesEvent(int nHandler, int eventType, CCSet *pTouches) = 0;
    
    // execute a schedule function
    virtual int executeSchedule(int nHandler, float dt) = 0;
};

/**
 CCScriptEngineManager is a singleton which holds an object instance of CCScriptEngineProtocl
 It helps cocos2d-x and the user code to find back LuaEngine object
 @since v0.99.5-x-0.8.5
 */
class CC_DLL CCScriptEngineManager
{
public:
    ~CCScriptEngineManager(void);
    
    CCScriptEngineProtocol* getScriptEngine(void) {
        return m_pScriptEngine;
    }
    void setScriptEngine(CCScriptEngineProtocol *pScriptEngine);
    void removeScriptEngine(void);

    static CCScriptEngineManager* sharedManager(void);
    static void purgeSharedManager(void);

private:
    CCScriptEngineManager(void)
    : m_pScriptEngine(NULL)
    {
    }
    
    CCScriptEngineProtocol *m_pScriptEngine;
};

// end of script_support group
/// @}

NS_CC_END

#endif // __SCRIPT_SUPPORT_H__
