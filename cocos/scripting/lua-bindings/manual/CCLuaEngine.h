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

/**@~english
 * The LuaEngine integrated into the cocos2d-x to process the interactive operation between lua and c++.
 *
 * @~chinese 
 * LuaEngine集成到cocos2d-x中，用于处理Lua和c++之间的交互操作。
 * 
 * @lua NA
 * @js NA
 */

class LuaEngine : public ScriptEngineProtocol
{
public:
    /**@~english
     * Get instance of LuaEngine.
     *
     * @~chinese 
     * 获取LuaEngine的实例。
     * 
     * @return @~english the instance of LuaEngine.
     * @~chinese LuaEngine的实例。
     */

    static LuaEngine* getInstance(void);
    /**@~english
     * Get defaultEngine of LuaEngine, it was deprecated.
     *
     * @~chinese 
     * 获取LuaEngine的默认实例,将被弃用。
     * 
     * @return @~english the instance of LuaEngine.
     * @~chinese LuaEngine的实例。
     */

    CC_DEPRECATED_ATTRIBUTE static LuaEngine* defaultEngine(void) { return LuaEngine::getInstance(); }
    
    /** @~english
     * Destructor of LuaEngine.
     * @~chinese 
     * LuaEngine的析构函数。
     */

    virtual ~LuaEngine(void);
    
    /**@~english
     * Get ccScriptType of LuaEngine used, it is always kScriptTypeLua.
     *
     * @~chinese 
     * 获取LuaEngine使用的ccScriptType值,它总是kScriptTypeLua。
     * 
     * @return @~english kScriptTypeLua.
     * @~chinese kScriptTypeLua。
     */

    virtual ccScriptType getScriptType() override {
        return kScriptTypeLua;
    };
    
    /**@~english
     * Get LuaStack of the LuaEngine.
     * All the interactive operation are all base on the LuaStack.
     *
     * @~chinese 
     * 获取LuaEngine的LuaStack。
     * 所有c++和Lua的交互操作都是基于LuaStack。
     * 
     * @return @~english LuaStack object.
     * @~chinese LuaStack对象。
     */

    LuaStack *getLuaStack(void) {
        return _stack;
    }
    
    /**@~english
     * Add a path to find Lua files in.
     *
     * @~chinese 
     * 添加一条查找Lua文件的搜索路径。
     * 
     * @param path @~english to be added to the Lua path.
     * @~chinese 新增的Lua文件搜索路径。
     */

    virtual void addSearchPath(const char* path);
    
    /**@~english
     * Add Lua loader.
     *
     * @~chinese 
     * 添加Lua加载器。
     * 
     * @param func @~english a function pointer point to the loader function.
     * @~chinese 指向加载器的函数指针。
     */

    virtual void addLuaLoader(lua_CFunction func);
    
    /**@~english
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the vaule nil.Then,it calls executeString function.
     *
     * @~chinese 
     * 重新加载对应moduleFileName指向的脚本文件。
     * 如果package["loaded"][moduleFileName]值不为nil,它将先设置值为nil,然后,调用executeString函数。
     * 
     * @param moduleFileName @~english String object holding the filename of the script file that is to be executed.
     * @~chinese 脚本文件的文件名。
     * @return @~english 0 if the string is excuted correctly or other if the string is excuted wrongly.
     * @~chinese 如果excuted正确,返回0。如果excuted错误则返回其它值。
     */

    virtual int reload(const char* moduleFileName);
    
    /**@~english
     * Remove the related reference about the Ref object stored in the Lua table by set the value of corresponding key nil:
     * The related Lua tables are toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root and object_Metatable["tolua_ubox"] or tolua_ubox.
     * Meanwhile set the corresponding userdata nullptr and remove the all the lua function refrence corresponding to this object.
     * 
     * In current mechanism, this function is called in the destructor of Ref object, developer don't call this functions.
     *
     * @~chinese 
     * 通过操作相关Lua table,移除Ref对象在Lua table中的引用。
     * 相关的Lua table包括toluafix_refid_ptr_mapping、toluafix_refid_type_mapping tolua_value_root和object_Metatable["tolua_ubox"]或tolua_ubox。
     * 同时，设置相应的userdata为nullptr以及移除去该对象相关的Lua函数的引用。
     * 
     * 目前的机制下，开发者不调用这个函数，这个函数将会在LuaEngier的析构函数中自动被调用。
     * 
     * @param object @~english the key object to remove script object.
     * @~chinese 用于移除脚本对象的键值。
     */

    virtual void removeScriptObjectByObject(Ref* object) override;
    
    /**@~english
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @~chinese 
     * 通过设置toluafix_refid_function_mapping[nHandle]=nil,移除Lua函数引用,。
     * 
     * @param nHandler @~english the function refrence index to find the correspoinding Lua function pointer.
     * @~chinese Lua函数的引用id。
     */

    virtual void removeScriptHandler(int nHandler) override;
    
    /**@~english
     * Reallocate Lua function reference index to the Lua function pointer to add refrence.
     *
     * @~chinese 
     * 重新分配Lua函数的引用id。
     * 
     * @param nHandler @~english the function refrence index to find the correspoinding Lua function pointer.
     * @~chinese Lua函数的引用id。
     */

    virtual int reallocateScriptHandler(int nHandler) override;
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * 执行给定字符串中包含的脚本代码。
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese 需被执行的脚本代码字符串。
     * @return @~english 0 if the string is excuted correctly,other if the string is excuted wrongly.
     * @~chinese 执行成功返回0，否则返回其它值。
     */

    virtual int executeString(const char* codes) override;
    
    /**@~english
     * Execute a script file.
     *
     * @~chinese 
     * 执行一个脚本文件。
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese 脚本文件的文件名。
     * @return @~english  0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese 如果碰到错误或者执行结果没有返回值返回0，否则返回1。
     */

    virtual int executeScriptFile(const char* filename) override;
    
    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @~chinese 
     * 执行全局的脚本函数。
     * 该全局函数不应该有任何参数,同时返回一个整数。
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese 全局脚本函数的字符串名称。
     * @return @~english The integer value returned from the script function.
     * @~chinese 从脚本函数返回的整数值。
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
    /**@~english
     * Handle the assert message.
     *
     * @~chinese 
     * 处理断言信息。
     * 
     * @return @~english return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false.
     * @~chinese 返回true,如果当前LuaStack的_callFromLua不等于0,否则返回假。
     */

    virtual bool handleAssert(const char *msg) override;
    
    /**@~english
     * Parse the config information data.
     * 
     * @~chinese 
     * 解析配置信息。
     * 
     * @param type @~english in current mechanism,it always ConfigType::COCOSTUDIO.
     * @~chinese 在当前的机制下,它总是ConfigType::COCOSTUDIO。
     * @param str  @~english the information data.
     * @~chinese 数据的信息。
     * @return @~english if __onParseConfig function exist in the Lua, it return the value that _stack->executeFunction returns otherwise return false.
     * @~chinese 如果__onParseConfig Lua函数存在时,它的返回值和执行_stack->executeFunction返回值一样，否则返回false。
     */

    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    
    /**@~english
     * When some events triggered in the c++ also needs to pass on to lua to handle, we could call this function to send events.
     *
     * @~chinese 
     * 当c++中触发的一些事件需要传递到Lua层处理时,调用这个函数来发送事件。
     * 
     * @param message @~english the ScriptEvent object that has ScriptEventType and the pointer to information data.
     * @~chinese ScriptEvent对象，包含有ScriptEventType和信息数据的指针。
     * @return @~english default return 0 otherwise return values the same as handleNodeEvent, handleMenuClickedEvent or handleCallFuncActionEvent,etc.
     * @~chinese 默认返回0,否则返回值和handleNodeEvent,handleMenuClickedEvent或handleCallFuncActionEvent等等一样。
     */

    virtual int sendEvent(ScriptEvent* message) override;
    
    /**@~english
     * Pass on the events related with ScrollView,TableCell,AssertManager, Armature, Accelerometer, Keyboard, Touch, Touches ,Mouse and Custom event to lua to handle.
     *
     * @~chinese 
     * 把与ScrollView,TableCell,AssertManager,Armature,Accelerometer,Keyboard,Touch,Touches, Mouse以及自定义事件相关的事件传递给Lua处理。
     * 
     * @param type @~english Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @~chinese 不同的ScriptHandlerMgr::HandlerType意味着不同的数据处理流程。
     * @param data @~english The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @~chinese 数据信息指针，根据不同的ScriptHandlerMgr::HandlerType，它在函数内部被解析成不同的数据，然后作为函数参数压入到Lua堆栈。
     * @return @~english default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     * @~chinese 默认返回0,否则根据不同的ScriptHandlerMgr::HandlerType，返回值也不同。
     */

    virtual int handleEvent(ScriptHandlerMgr::HandlerType type,void* data);
    /**@~english
     * Pass on the events related with TableCell and TableView to lua to handle.
     *
     * @~chinese 
     * 把与TableCell,TableView相关的事件传递给Lua处理。
     * 
     * @param type @~english Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @~chinese 不同的ScriptHandlerMgr::HandlerType意味着不同的数据处理流程。
     * @param data @~english The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @~chinese 数据信息指针，根据不同的ScriptHandlerMgr::HandlerType，它在函数内部被解析成不同的数据，然后作为函数参数压入到Lua堆栈。
     * @param numResults @~english The number of the return values.
     * @~chinese 返回值的数量。
     * @param func @~english The callback would be called when numResults is > 0.
     * @~chinese 当numResults > 0时将会调用的回调方法。
     * @return @~english default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     * @~chinese 默认返回0,否则根据不同的ScriptHandlerMgr::HandlerType，返回值也不同。
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
