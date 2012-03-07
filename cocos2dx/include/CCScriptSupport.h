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

#include "CCCommon.h"
#include "CCTouch.h"
#include "CCSet.h"

typedef struct lua_State lua_State;

NS_CC_BEGIN

class CCTimer;

// Lua support for CCScheduler
class CCSchedulerScriptHandlerEntry : public CCObject
{
public:
    // nHandler return by tolua_ref_function(), called from LuaCocos2d.cpp
    static CCSchedulerScriptHandlerEntry* entryWithHandler(int nHandler, ccTime fInterval, bool bPaused);
    ~CCSchedulerScriptHandlerEntry(void);
    
    inline cocos2d::CCTimer* getTimer(void) {
        return m_pTimer;
    }
    
    inline bool isPaused(void) {
        return m_bPaused;
    }
    
    inline int getEntryID(void) {
        return m_nEntryID;
    }
    
    inline void markedForDeletion(void) {
        m_bMarkedForDeletion = true;
    }
    
    inline bool isMarkedForDeletion(void) {
        return m_bMarkedForDeletion;
    }
    
private:
    CCSchedulerScriptHandlerEntry(void);
    bool initWithHandler(int nHandler, ccTime fInterval, bool bPaused);
    
    cocos2d::CCTimer*   m_pTimer;
    bool                m_bPaused;
    bool                m_bMarkedForDeletion;
    int                 m_nHandler;
    int                 m_nEntryID;
};


// Lua support for touch events
class CCTouchScriptHandlerEntry : public CCObject
{
public:
    static CCTouchScriptHandlerEntry* entryWithHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    ~CCTouchScriptHandlerEntry(void);
    
    inline int getHandler(void) {
        return m_nHandler;
    }
    
    inline bool getIsMultiTouches(void) {
        return m_bIsMultiTouches;
    }
    
    inline int getPriority(void) {
        return m_nPriority;
    }
    
    inline bool getSwallowsTouches(void) {
        return m_bSwallowsTouches;
    }
    
private:
    CCTouchScriptHandlerEntry(void);
    bool initWithHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    
    int     m_nHandler;
    bool    m_bIsMultiTouches;
    int     m_nPriority;
    bool    m_bSwallowsTouches;
};


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
    virtual int executeFunctionByHandler(int nHandler, int numArgs = 0) = 0;
    virtual int executeFunctionWithIntegerData(int nHandler, int data) = 0;
    virtual int executeFunctionWithFloatData(int nHandler, float data) = 0;
    virtual int executeFunctionWithBooleanData(int nHandler, bool data) = 0;
    virtual int executeFunctionWithCCObject(int nHandler, CCObject* pObject, const char* typeName) = 0;    
    virtual int pushIntegerToLuaStack(int data) = 0;
    virtual int pushFloatToLuaStack(int data) = 0;
    virtual int pushBooleanToLuaStack(int data) = 0;
    virtual int pushCCObjectToLuaStack(CCObject* pObject, const char* typeName) = 0;
    
    // functions for excute touch event
    virtual int executeTouchEvent(int nHandler, int eventType, CCTouch *pTouch) = 0;
    virtual int executeTouchesEvent(int nHandler, int eventType, CCSet *pTouches) = 0;
    
    // execute a schedule function
    virtual int executeSchedule(int nHandler, ccTime dt) = 0;
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

NS_CC_END

#endif // __SCRIPT_SUPPORT_H__
