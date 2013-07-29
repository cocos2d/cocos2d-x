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
#include "CCLuaStack.h"
#include "CCLuaValue.h"

NS_CC_BEGIN

// Lua support for cocos2d-x
class LuaEngine : public ScriptEngineProtocol
{
public:
    static LuaEngine* getInstance(void);
    CC_DEPRECATED_ATTRIBUTE static LuaEngine* defaultEngine(void) { return LuaEngine::getInstance(); }
    virtual ~LuaEngine(void);
    
    virtual ccScriptType getScriptType() {
        return kScriptTypeLua;
    };

    LuaStack *getLuaStack(void) {
        return _stack;
    }
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path);
    
    /**
     @brief Add lua loader, now it is used on android
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     @brief Remove Object from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByObject(Object* pObj);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Reallocate Lua function reference
     */
    virtual int reallocateScriptHandler(int nHandler);
    
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

    virtual int executeNodeEvent(Node* pNode, int nAction);
    virtual int executeMenuItemEvent(MenuItem* pMenuItem);
    virtual int executeNotificationEvent(NotificationCenter* pNotificationCenter, const char* pszName);
    virtual int executeCallFuncActionEvent(CallFunc* pAction, Object* pTarget = NULL);
    virtual int executeSchedule(int nHandler, float dt, Node* pNode = NULL);
    virtual int executeLayerTouchesEvent(Layer* pLayer, int eventType, Set *pTouches);
    virtual int executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch);
    virtual int executeLayerKeypadEvent(Layer* pLayer, int eventType);
    /** execute a accelerometer event */
    virtual int executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue);
    virtual int executeEvent(int nHandler, const char* pEventName, Object* pEventSource = NULL, const char* pEventSourceClassName = NULL);

    virtual bool handleAssert(const char *msg);
    
    virtual int sendEvent(ScriptEvent* message);
    void extendLuaObject();
private:
    LuaEngine(void)
    : _stack(NULL)
    {
    }
    bool init(void);
    int handleNodeEvent(void* data);
    int handleMenuClickedEvent(void* data);
    int handleNotificationEvent(void* data);
    int handleCallFuncActionEvent(void* data);
    int handleScheduler(void* data);
    int handleKeypadEvent(void* data);
    int handleAccelerometerEvent(void* data);
    int handleCommonEvent(void* data);
    int handleTouchEvent(void* data);
    int handleTouchesEvent(void* data);
    int handlerControlEvent(void* data);
    void extendNode(lua_State* lua_S);
    void extendMenuItem(lua_State* lua_S);
    void extendLayer(lua_State* lua_S);
    void extendControl(lua_State* lua_S);
    void extendWebsocket(lua_State* lua_S);
    void extendGLNode(lua_State* lua_S);
    void extendScrollView(lua_State* lua_S);
    void extendDrawNode(lua_State* lua_S);
private:
    static LuaEngine* _defaultEngine;
    LuaStack *_stack;
};

NS_CC_END

#endif // __CC_LUA_ENGINE_H__
