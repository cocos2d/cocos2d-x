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
class CCSchedulerFuncEntry : public CCObject
{
public:
    // uFuncID return by tolua_ref_function(), called from LuaCocos2d.cpp
    static CCSchedulerFuncEntry* entryWithFuncID(int uFuncID, ccTime fInterval, bool bPaused);
    ~CCSchedulerFuncEntry(void);
    
    inline cocos2d::CCTimer* getTimer(void) {
        return m_pTimer;
    }
    
    inline bool isPaused(void) {
        return m_bPaused;
    }
    
    inline int getEntryID(void) {
        return m_uEntryID;
    }
    
    inline void markedForDeletion(void) {
        m_bMarkedForDeletion = true;
    }
    
    inline bool isMarkedForDeletion(void) {
        return m_bMarkedForDeletion;
    }
    
private:
    CCSchedulerFuncEntry(void);
    bool initWithuFuncID(int uFuncID, ccTime fInterval, bool bPaused);
    
    cocos2d::CCTimer*   m_pTimer;
    bool                m_bPaused;
    bool                m_bMarkedForDeletion;
    unsigned int        m_uFuncID;
    unsigned int        m_uEntryID;
};


// Lua support for touch events
class CCTouchEventEntry : public CCObject
{
public:
    static CCTouchEventEntry* entryWithuFuncID(int uFuncID);
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
    void removeCCObjectByID(unsigned int uLuaID);
    
    /**
     @brief Remove Lua function reference
     */
    void removeLuaFuncID(int uFuncID);
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    void addSearchPath(const char* path);
    
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
    int executeFunctionByRefID(int uFuncID, int numArgs = 0);
    int executeFunctionWithIntegerData(int uFuncID, int data);
    int executeFunctionWithFloatData(int uFuncID, float data);
    int executeFunctionWithBooleanData(int uFuncID, bool data);
    
    // functions for excute touch event
    int executeTouchEvent(int uFuncID, int eventType, cocos2d::CCTouch *pTouch);
    int executeTouchesEvent(int uFuncID, int eventType, cocos2d::CCSet *pTouches);
    
    // execute a schedule function
    int executeSchedule(int uFuncID, cocos2d::ccTime dt);
    
    static CCLuaEngine* sharedEngine();
    static void purgeSharedEngine();
    
private:
    CCLuaEngine();
    
    static CCLuaEngine* s_engine;
    lua_State* m_state;
};
    
} // namespace cocos2d

#endif // __CC_LUA_ENGINE_H__
