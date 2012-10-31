/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

class CCTimer;
class CCLayer;
class CCMenuItem;
class CCNotificationCenter;
class CCCallFunc;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

// #pragma mark -
// #pragma mark CCScriptHandlerEntry

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

/**
 * @addtogroup script_support
 * @{
 */

// #pragma mark -
// #pragma mark CCSchedulerScriptHandlerEntry

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


// #pragma mark -
// #pragma mark CCTouchScriptHandlerEntry

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

// #pragma mark -
// #pragma mark CCScriptEngineProtocol

// Don't make CCScriptEngineProtocol inherits from CCObject since setScriptEngine is invoked only once in AppDelegate.cpp,
// It will affect the lifecycle of ScriptCore instance, the autorelease pool will be destroyed before destructing ScriptCore.
// So a crash will appear on Win32 if you click the close button.
class CC_DLL CCScriptEngineProtocol
{
public:
    virtual ~CCScriptEngineProtocol() {};
    
    /** Get script type */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** Remove script object. */
    virtual void removeScriptObjectByCCObject(CCObject* pObj) = 0;
    
    /** Remove script function handler, only CCLuaEngine class need to implement this function. */
    virtual void removeScriptHandler(int nHandler) {};
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is executed correctly.
     @return other if the string is executed wrongly.
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
     @brief Execute a node event function
     @param pNode which node produce this event
     @param nAction kCCNodeOnEnter,kCCNodeOnExit,kCCMenuItemActivated,kCCNodeOnEnterTransitionDidFinish,kCCNodeOnExitTransitionDidStart
     @return The integer value returned from the script function.
     */
    virtual int executeNodeEvent(CCNode* pNode, int nAction) = 0;
    
    virtual int executeMenuItemEvent(CCMenuItem* pMenuItem) = 0;
    /** Execute a notification event function */
    virtual int executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName) = 0;
    
    /** execute a callfun event */
    virtual int executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget = NULL) = 0;
    /** execute a schedule function */
    virtual int executeSchedule(CCTimer* pTimer, float dt, CCNode* pNode = NULL) = 0;
    
    /** functions for execute touch event */
    virtual int executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches) = 0;
    virtual int executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch) = 0;
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
