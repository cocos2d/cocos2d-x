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
#include "CCObject.h"
#include "CCTouch.h"
#include "CCSet.h"
#include "CCNode.h"

namespace cocos2d
{
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


// Lua support for cocos2d-x
class CCLuaEngine
{
public:
    ~CCLuaEngine();
    
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) {
        return m_state;
    }
    
    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    void removeCCObjectByID(int nLuaID);
    
    /**
     @brief Remove Lua function reference
     */
    void removeLuaHandler(int nHandler);
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    void addSearchPath(const char* path);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    int executeString(const char* codes);
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    int executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param function_name String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    int executeGlobalFunction(const char* function_name);
    
    /**
     @brief Execute a function by ref id
     @param The function ref id
     @param Number of parameters
     @return The integer value returned from the script function.
     */
    int executeFunctionByRefID(int nHandler, int numArgs = 0);
    int executeFunctionWithIntegerData(int nHandler, int data);
    int executeFunctionWithFloatData(int nHandler, float data);
    int executeFunctionWithBooleanData(int nHandler, bool data);
    
    // functions for excute touch event
    int executeTouchEvent(int nHandler, int eventType, cocos2d::CCTouch *pTouch);
    int executeTouchesEvent(int nHandler, int eventType, cocos2d::CCSet *pTouches);
    
    // execute a schedule function
    int executeSchedule(int nHandler, cocos2d::ccTime dt);
    
    // Add lua loader, now it is used on android
    void addLuaLoader(lua_CFunction func);
    
    static CCLuaEngine* sharedEngine();
    static void purgeSharedEngine();
    
private:
    CCLuaEngine();
    
    static CCLuaEngine* s_engine;
    lua_State* m_state;
};
    
} // namespace cocos2d

#endif // __CC_LUA_ENGINE_H__
