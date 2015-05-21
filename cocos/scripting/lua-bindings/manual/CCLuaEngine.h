/****************************************************************************
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "cocos2d.h"
#include "base/CCScriptSupport.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "cocos2d/LuaScriptHandlerMgr.h"

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

/**
 * The Lua engine integrated into the cocos2d-x to process the interactive operation between lua and c++.
 *
 * @lua NA
 * @js NA
 */
class LuaEngine : public ScriptEngineProtocol
{
public:
    /**
     * Get instance of LuaEngine.
     *
     * @return the instance of LuaEngine.
     */
    static LuaEngine* getInstance(void);
    /**
     * Get defaultEngine of LuaEngine, it was deprecated.
     *
     * @return the instance of LuaEngine.
     */
    CC_DEPRECATED_ATTRIBUTE static LuaEngine* defaultEngine(void) { return LuaEngine::getInstance(); }
    
    /** 
     * Destrutor of LuaEngine.
     */
    virtual ~LuaEngine(void);
    
    /**
     * Get ccScriptType of LuaEngine used, it is always kScriptTypeLua.
     *
     * @return kScriptTypeLua.
     */
    virtual ccScriptType getScriptType() override {
        return kScriptTypeLua;
    };
    
    /**
     * Get LuaStack of the LuaEngine.
     * All the interactive operation are all base on the LuaStack.
     *
     * @return LuaStack object.
     */
    LuaStack *getLuaStack(void) {
        return _stack;
    }
    
    /**
     * Add a path to find lua files in.
     *
     * @param path to be added to the Lua path.
     */
    virtual void addSearchPath(const char* path);
    
    /**
     * Add lua loader.
     *
     * @param func a function pointer point to the loader function.
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the vaule nil.Then,it calls executeString function.
     *
     * @param moduleFileName String object holding the filename of the script file that is to be executed.
     * @return 0 if the string is excuted correctly or other if the string is excuted wrongly.
     */
    virtual int reload(const char* moduleFileName);
    
    /**
     * Remove the related reference about the Ref object stored in the Lua table by set the value of corresponding key nil:
     * The related Lua tables are toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root and object_Metatable["tolua_ubox"] or tolua_ubox.
     * Meanwhile set the corresponding userdata nullptr and remove the all the lua function refrence corresponding to this object.
     * 
     * In current mechanism, this function is called in the destructor of Ref object, developer don't call this functions.
     *
     * @param object the key object to remove script object.
     */
    virtual void removeScriptObjectByObject(Ref* object) override;
    
    /**
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @param nHandler the function refrence index to find the correspoinding Lua function pointer.
     */
    virtual void removeScriptHandler(int nHandler) override;
    
    /**
     * Reallocate Lua function reference index to the Lua function pointer to add refrence.
     *
     * @param nHandler the function refrence index to find the correspoinding Lua function pointer.
     */
    virtual int reallocateScriptHandler(int nHandler) override;
    
    /**
     * Execute script code contained in the given string.
     *
     * @param codes holding the valid script code that should be executed.
     * @return 0 if the string is excuted correctly,other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes) override;
    
    /**
     * Execute a script file.
     *
     * @param filename String object holding the filename of the script file that is to be executed.
     * @return the return values by calling executeFunction.
     */
    virtual int executeScriptFile(const char* filename) override;
    
    /**
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     * @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName) override;
    virtual int executeNodeEvent(Node* pNode, int nAction);
    virtual int executeMenuItemEvent(MenuItem* pMenuItem);
    virtual int executeNotificationEvent(__NotificationCenter* pNotificationCenter, const char* pszName);
    virtual int executeCallFuncActionEvent(CallFunc* pAction, Ref* pTarget = NULL);
    virtual int executeSchedule(int nHandler, float dt, Node* pNode = NULL);
    virtual int executeLayerTouchesEvent(Layer* pLayer, int eventType, __Set *pTouches);
    virtual int executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch);
    virtual int executeLayerKeypadEvent(Layer* pLayer, int eventType);
    virtual int executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue);
    virtual int executeEvent(int nHandler, const char* pEventName, Ref* pEventSource = NULL, const char* pEventSourceClassName = NULL);
    /**
     * Handle the assert message.
     *
     * @return return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false.
     */
    virtual bool handleAssert(const char *msg) override;
    
    /**
     * Parse the config information data.
     * 
     * @param type in current mechanism,it always ConfigType::COCOSTUDIO.
     * @param str  the information data.
     * @return if __onParseConfig function exist in the Lua, it return the value that _stack->executeFunction returns otherwise return false.
     */
    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    
    /**
     * When some events triggered in the c++ also needs to pass on to lua to handle, we could call this function to send events.
     *
     * @param message the ScriptEvent object that has ScriptEventType and the pointer to information data.
     * @return default return 0 otherwise return values the same as handleNodeEvent, handleMenuClickedEvent or handleCallFuncActionEvent,etc.
     */
    virtual int sendEvent(ScriptEvent* message) override;
    
    /**
     * Pass on the events related with ScrollView,TableCell,AssertManager, Armature, Accelerometer, Keyboard, Touch, Touches ,Mouse and Custom event to lua to handle.
     *
     * @param type Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @param data The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @return default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     */
    virtual int handleEvent(ScriptHandlerMgr::HandlerType type,void* data);
    /**
     * Pass on the events related with TableCell and TableView to lua to handle.
     *
     * @param type Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @param data The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @param numResults The number of the return values.
     * @param func The callback would be called when numResults is > 0.
     * @return default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     */
    virtual int handleEvent(ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);
private:
    LuaEngine(void)
    : _stack(nullptr)
    {
    }
    bool init(void);
    int handleNodeEvent(void* data);
    int handleMenuClickedEvent(void* data);
    int handleCallFuncActionEvent(void* data);
    int handleScheduler(void* data);
    int handleKeypadEvent(void* data);
    int handleAccelerometerEvent(void* data);
    int handleCommonEvent(void* data);
    int handleTouchEvent(void* data);
    int handleTouchesEvent(void* data);
    int handlerControlEvent(void* data);
    int handleEvenCustom(void* data);
    int handleAssetsManagerEvent(ScriptHandlerMgr::HandlerType type,void* data);
    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data);
    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data, int numResults, const std::function<void(lua_State*,int)>& func);
    int handleArmatureWrapper(ScriptHandlerMgr::HandlerType type,void* data);
    int handleEventAcc(void* data);
    int handleEventKeyboard(ScriptHandlerMgr::HandlerType type,void* data);
    int handleEventTouch(ScriptHandlerMgr::HandlerType type, void* data);
    int handleEventTouches(ScriptHandlerMgr::HandlerType type, void* data);
    int handleEventMouse(ScriptHandlerMgr::HandlerType type, void* data);
    
private:
    static LuaEngine* _defaultEngine;
    LuaStack *_stack;
};

NS_CC_END

// end group
/// @}

#endif // __CC_LUA_ENGINE_H__
