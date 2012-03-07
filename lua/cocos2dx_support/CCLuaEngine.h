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
#include "CCScriptSupport.h"

NS_CC_BEGIN

// Lua support for cocos2d-x
class CCLuaEngine : public CCScriptEngineProtocol
{
public:
    ~CCLuaEngine();
    
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
    virtual void removeCCObjectByID(int nLuaID);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeLuaHandler(int nHandler);
    
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
    
    /**
     @brief Execute a function by ref id
     @param The function ref id
     @param Number of parameters
     @return The integer value returned from the script function.
     */
    virtual int executeFunctionByHandler(int nHandler, int numArgs = 0);
    virtual int executeFunctionWithIntegerData(int nHandler, int data);
    virtual int executeFunctionWithFloatData(int nHandler, float data);
    virtual int executeFunctionWithBooleanData(int nHandler, bool data);
    virtual int executeFunctionWithCCObject(int nHandler, CCObject* pObject, const char* typeName);    
    virtual int pushIntegerToLuaStack(int data);
    virtual int pushFloatToLuaStack(int data);
    virtual int pushBooleanToLuaStack(int data);
    virtual int pushCCObjectToLuaStack(CCObject* pObject, const char* typeName);
    
    // functions for excute touch event
    virtual int executeTouchEvent(int nHandler, int eventType, cocos2d::CCTouch *pTouch);
    virtual int executeTouchesEvent(int nHandler, int eventType, cocos2d::CCSet *pTouches);
    
    // execute a schedule function
    virtual int executeSchedule(int nHandler, cocos2d::ccTime dt);
    
    // Add lua loader, now it is used on android
    virtual void addLuaLoader(lua_CFunction func);
    
    static CCLuaEngine* engine();
    
private:
    CCLuaEngine(void)
    : m_state(NULL)
    {
    }
    
    bool init(void);
    bool pushFunctionByHandler(int nHandler);
    
    lua_State* m_state;
};
    
NS_CC_END

#endif // __CC_LUA_ENGINE_H__
